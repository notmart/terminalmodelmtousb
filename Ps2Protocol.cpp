/*
 *   Copyright 2021 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Ps2Protocol.hh"

void Ps2Protocol_::begin(uint8_t clockPin, uint8_t dataPin)
{
    m_clockPin = clockPin;
    m_dataPin = dataPin;

    pinMode(m_clockPin, INPUT_PULLUP);
    pinMode(m_dataPin, INPUT_PULLUP);

    m_scancodeCacheReadPos = 0;
    m_scancodeCacheWritePos = 0;

    for (uint32_t i = 0; i < PS2MESSAGE_CACHE_SIZE; ++i) {
        m_scancodeCache[i] = 0;
        m_scancodeCacheUnreadBits[i] = false;
    }

    reset();

    attachInterrupt(digitalPinToInterrupt(clockPin), Ps2Protocol_::ps2Interrupt, FALLING);
}

void Ps2Protocol_::reset()
{
    m_incomingMessage = 0;
    m_outgoingMessage = 0;

    m_bitCount = 0;
    m_parityCount = 0;
    m_lastInterruptMillis = millis();
    m_readMode = true;
}

void Ps2Protocol_::ps2Interrupt()
{
    if (Ps2Protocol.m_readMode) {
        readBitFromInterrupt();
    } else {
        writeBitFromInterrupt();
    }
}

void Ps2Protocol_::readBitFromInterrupt()
{
    uint8_t val = digitalRead(Ps2Protocol.m_dataPin);
    const uint32_t currentMillis = millis();

    // Either too much time is passed since last interrupt: treat the interrupt as the start of a new message
    // Or bits for a new message are already arriving
    if (currentMillis - Ps2Protocol.m_lastInterruptMillis > 250) {
        Ps2Protocol.reset();
    }

    Ps2Protocol.m_lastInterruptMillis = currentMillis;

    ++Ps2Protocol.m_bitCount;

    switch (Ps2Protocol.m_bitCount) {
    // The first incoming bit must always be 0, if not, protocol error;
    case 1:
        if (val != 0) {
            Ps2Protocol.reset();
            return;
        }
        break;
    // Data bits
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        Ps2Protocol.m_incomingMessage |= (val << (Ps2Protocol.m_bitCount - 2));
        Ps2Protocol.m_parityCount += val;
        break;
    // Check parity bit
    case 10:
        if (val == (Ps2Protocol.m_parityCount & 1)) {
            Ps2Protocol.reset();
            return;
        }
        break;
    // Put scancode into buffer if 
    case 11:
        if (val == 0) {
            Ps2Protocol.reset();
        }
        Ps2Protocol.m_scancodeCacheWritePos = (Ps2Protocol.m_scancodeCacheWritePos + 1) % PS2MESSAGE_CACHE_SIZE;
        Ps2Protocol.m_scancodeCache[Ps2Protocol.m_scancodeCacheWritePos] = Ps2Protocol.m_incomingMessage;
        Ps2Protocol.m_scancodeCacheUnreadBits[Ps2Protocol.m_scancodeCacheWritePos] = true;
        Ps2Protocol.reset();
        break;
    default:
        Ps2Protocol.reset();
    }
}

void Ps2Protocol_::writeBitFromInterrupt()
{
    uint8_t currentBit = 0;
    ++Ps2Protocol.m_bitCount;

    switch (Ps2Protocol.m_bitCount) {
        case 1:
            digitalWrite(Ps2Protocol.m_dataPin, LOW);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            currentBit = (Ps2Protocol.m_outgoingMessage >> (Ps2Protocol.m_bitCount - 2)) & 1;
            digitalWrite(Ps2Protocol.m_dataPin, currentBit);
            Ps2Protocol.m_parityCount += currentBit;
            break;

        case 10:
            digitalWrite(Ps2Protocol.m_dataPin, (~Ps2Protocol.m_parityCount & 1));
            break;

        case 11:
            //Ps2Protocol.reset();
            pinMode(Ps2Protocol.m_dataPin, INPUT_PULLUP);
            break;

        case 12:
            Ps2Protocol.reset();
            break;

        default:
            Ps2Protocol.reset();
    }
}

uint8_t Ps2Protocol_::popScancode()
{
    m_scancodeCacheReadPos = (m_scancodeCacheReadPos + 1) % PS2MESSAGE_CACHE_SIZE;
    if (m_scancodeCacheUnreadBits[m_scancodeCacheReadPos]) {
        m_scancodeCacheUnreadBits[m_scancodeCacheReadPos] = false;
       // Serial.println(m_scancodeCache[m_scancodeCacheReadPos]);
        return m_scancodeCache[m_scancodeCacheReadPos];
    }

    return 0;
}

void Ps2Protocol_::sendMessage(uint8_t message) {
  Serial.println("Sending");
    reset();
    noInterrupts();

    m_readMode = false;
    pinMode(m_dataPin, OUTPUT);
    pinMode(m_clockPin, OUTPUT);
    digitalWrite(m_dataPin, HIGH);
    digitalWrite(m_clockPin, HIGH);

    delayMicroseconds(10);

    // Tell The keyboard we are about to send a message
    digitalWrite(m_clockPin, LOW);
    delayMicroseconds(60);

    digitalWrite(m_dataPin, LOW);
 
    // write of the bits will be done at clock ticks from the keyboard
    pinMode(m_clockPin, INPUT_PULLUP);
    m_outgoingMessage = message;

   // pinMode(m_dataPin, OUTPUT);
  
    // Header bit is 0
    //digitalWrite(m_dataPin, LOW);

    interrupts();
}

Ps2Protocol_ Ps2Protocol;
