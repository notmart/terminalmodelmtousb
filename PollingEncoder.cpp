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

#include "PollingEncoder.hh"

PollingEncoder::PollingEncoder(uint8_t leftPin, uint8_t rightPin, uint8_t buttonPin)
    : m_leftPin(leftPin),
      m_rightPin(rightPin),
      m_buttonPin(buttonPin)
{
    pinMode(m_leftPin, INPUT_PULLUP);
    pinMode(m_rightPin, INPUT_PULLUP);

    pinMode(m_buttonPin, INPUT);
}

PollingEncoder::Direction PollingEncoder::pollDirection()
{
    const int leftBit = digitalRead(m_leftPin);
    const int rightBit = digitalRead(m_rightPin);

    const int encoded = (leftBit << 1) | rightBit;

    const int bothEncoded = (m_lastEncoded << 2) | encoded;

    Direction ret = None;

    switch (bothEncoded) {
    case 0b1000:
        Serial.println("Left");
        ret = Left;
        break;
    case 0b0010:
        Serial.println("Right");
        ret = Right;
        break;
    default:
        break;
    }

    m_lastEncoded = encoded;

    return ret;
}

PollingEncoder::ButtonState PollingEncoder::pollButton()
{
    const ButtonState buttonState = digitalRead(m_buttonPin) ? Pressed : Released;

    if (m_lastButtonState != buttonState) {
        m_lastButtonState = buttonState;
        return m_lastButtonState;
    } else {
        return Unchanged;
    }
}
