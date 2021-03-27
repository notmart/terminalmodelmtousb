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

#ifndef PS2PROTOCOL_H
#define PS2PROTOCOL_H

#include <Arduino.h>

#define PS2MESSAGE_CACHE_SIZE 48

class Ps2Protocol_ {
public:
    void begin(uint8_t clockPin, uint8_t dataPin);

    uint8_t popScancode();
    void sendMessage(uint8_t);
    

private:
    static void ps2Interrupt();
    static inline void readBitFromInterrupt();
    static inline void writeBitFromInterrupt();
    void reset();


    uint8_t m_clockPin;
    uint8_t m_dataPin;

    // access the cached messages
    uint8_t m_scancodeCache[PS2MESSAGE_CACHE_SIZE];
    uint8_t m_scancodeCacheUnreadBits[PS2MESSAGE_CACHE_SIZE];
    uint8_t m_scancodeCacheWritePos;
    uint8_t m_scancodeCacheReadPos;

    uint8_t m_incomingMessage;
    uint8_t m_outgoingMessage;
    uint8_t m_bitCount;
    uint8_t m_parityCount;
    uint32_t m_lastInterruptMillis;

    bool m_readMode;
};

extern Ps2Protocol_ Ps2Protocol;

#endif
