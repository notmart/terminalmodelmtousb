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

#ifndef POLLINGENCODER_H
#define POLLINGENCODER_H

#include <Arduino.h>


class PollingEncoder {
public:
    enum Direction {
        None,
        Left,
        Right
    };

    enum ButtonState {
        Unchanged,
        Pressed,
        Released
    };

    PollingEncoder(uint8_t leftPin, uint8_t rightPin, uint8_t buttonPin);


    PollingEncoder::Direction pollDirection();
    PollingEncoder::ButtonState pollButton();

private:
    const static uint8_t  s_buttonDebounceDelay = 50;
    long m_lastButtonDebounceTime = 0;
    uint8_t m_leftPin;
    uint8_t m_rightPin;
    uint8_t m_buttonPin;

    uint8_t m_lastEncoded = None;
    uint8_t m_lastButtonState = Unchanged;
};


#endif
