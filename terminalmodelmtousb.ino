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

// Depends upon https://github.com/NicoHood/HID
#include "HID-Project.h"

#include "KeyTable.h"
#include "Ps2Protocol.hh"

// when turned on keyboard sends AA BF B6 when this equals 3 all 3 codes arrived
// default to sequence done for now, investigate how to always make it send the sequence
// even when starts together with the arduino
static volatile uint8_t aabfb6_status = 0;

#define DATA_PIN 3
#define IRQ_PIN 2

#define numLockLed 10
#define capsLed 11 


void setup() {
    setup_key_table();
    Serial.begin(9600);
    BootKeyboard.begin();

    pinMode(IRQ_PIN, INPUT_PULLUP);
    pinMode(DATA_PIN, INPUT_PULLUP);

    Ps2Protocol.begin(IRQ_PIN, DATA_PIN);

    // Ask the keyboard to send Make and Break codes (in case it's already connected)
    Ps2Protocol.sendMessage(0xF8);
}

void loop() {
    const uint8_t ledsStatus = BootKeyboard.getLeds();
    if (ledsStatus & LED_NUM_LOCK) {
        digitalWrite(numLockLed, HIGH);
    } else {
        digitalWrite(numLockLed, LOW);
    }
    if (ledsStatus & LED_CAPS_LOCK) {
        digitalWrite(capsLed, HIGH);
    } else {
        digitalWrite(capsLed, LOW);
    }
    if (ledsStatus & LED_SCROLL_LOCK) {
        digitalWrite(capsLed, HIGH);
    } else {
        digitalWrite(capsLed, LOW);
    }

    static bool next_is_break = true;
    uint8_t scan_code = Ps2Protocol.popScancode();

    if (scan_code) {
        Serial.println(scan_code, HEX);

        switch (aabfb6_status) {
        case 0:
            if (scan_code == 0xAA) {
                aabfb6_status = 1;
            }
            return;
        case 1:
            if (scan_code == 0xBF) {
                aabfb6_status = 2;
            }
            return;
        case 2:
            if (scan_code == 0xB6) {
                aabfb6_status = 3;
               // Ask the keyboard to send Make and Break codes
               Ps2Protocol.sendMessage(0xF8);
            }
            return;  
        case 3:
        default:
            break;
        }


        if (scan_code == 0xF0) {
            next_is_break = true;
        } else {
            if (next_is_break) {
                BootKeyboard.release(key_table[scan_code]);
            } else {
                BootKeyboard.press(key_table[scan_code]);
            }
            next_is_break = false;
        }
    }
}
