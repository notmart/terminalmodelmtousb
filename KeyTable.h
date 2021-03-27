#ifndef KEYTABLE_H
#define KEYTABLE_H

#include "HID-Project.h"

static KeyboardKeycode key_table[256];

void setup_key_table()
{
    //default to zero which won't send anything
    for (int i = 0; i < 256; ++i) {
        key_table[i] = KEY_RESERVED;
    }

    // Numer row
    key_table[0xE] = KEY_TILDE;
    key_table[0x16] = KEY_1;
    key_table[0x1E] = KEY_2;
    key_table[0x26] = KEY_3;
    key_table[0x25] = KEY_4;
    key_table[0x2E] = KEY_5;
    key_table[0x36] = KEY_6;
    key_table[0x3D] = KEY_7;
    key_table[0x3E] = KEY_8;
    key_table[0x46] = KEY_9;
    key_table[0x45] = KEY_0;
    key_table[0x4E] = KEY_MINUS;
    key_table[0x55] = KEY_EQUAL;

    // Q ROW
    key_table[0x15] = KEY_Q;
    key_table[0x1D] = KEY_W;
    key_table[0x24] = KEY_E;
    key_table[0x2D] = KEY_R;
    key_table[0x2C] = KEY_T;
    key_table[0x35] = KEY_Y;
    key_table[0x3C] = KEY_U;
    key_table[0x43] = KEY_I;
    key_table[0x44] = KEY_O;
    key_table[0x4d] = KEY_P;
    key_table[0x54] = KEY_LEFT_BRACE;
    key_table[0x5B] = KEY_RIGHT_BRACE;

    key_table[0x1C] = KEY_A;
    key_table[0x1B] = KEY_S;
    key_table[0x23] = KEY_D;
    key_table[0x2B] = KEY_F;
    key_table[0x34] = KEY_G;
    key_table[0x33] = KEY_H;
    key_table[0x3B] = KEY_J;
    key_table[0x42] = KEY_K;
    key_table[0x4B] = KEY_L;
    key_table[0x4C] = KEY_SEMICOLON;
    key_table[0x52] = KEY_QUOTE;
    key_table[0x53] = KEY_BACKSLASH;

    key_table[0x13] = KEY_NON_US;
    key_table[0x1A] = KEY_Z;
    key_table[0x22] = KEY_X;
    key_table[0x21] = KEY_C;
    key_table[0x2A] = KEY_V;
    key_table[0x32] = KEY_B;
    key_table[0x31] = KEY_N;
    key_table[0x3A] = KEY_M;
    key_table[0x41] = KEY_COMMA;
    key_table[0x49] = KEY_PERIOD;
    key_table[0x4A] = KEY_SLASH;

    // Command keys
    key_table[0x0D] = KEY_TAB;
    key_table[0x14] = KEY_CAPS_LOCK;
    key_table[0x12] = KEY_LEFT_SHIFT;
    key_table[0x11] = KEY_LEFT_CTRL;
    key_table[0x19] = KEY_LEFT_ALT;
    key_table[0x29] = KEY_SPACE;
    key_table[0x39] = KEY_RIGHT_ALT;
    key_table[0x58] = KEY_RIGHT_CTRL;
    key_table[0x59] = KEY_RIGHT_SHIFT;
    key_table[0x5a] = KEY_ENTER;
    key_table[0x66] = KEY_BACKSPACE;

    // Function rows
    key_table[0x07] = KEY_F1;
    key_table[0x0F] = KEY_F2;
    key_table[0x17] = KEY_F3;
    key_table[0x1F] = KEY_F4;
    key_table[0x27] = KEY_F5;
    key_table[0x2F] = KEY_F6;
    key_table[0x37] = KEY_F7;
    key_table[0x3F] = KEY_F8;
    key_table[0x47] = KEY_F9;
    key_table[0x4F] = KEY_F10;
    key_table[0x56] = KEY_F11;
    key_table[0x5E] = KEY_F12;

    key_table[0x08] = KEY_F13;
    key_table[0x10] = KEY_F14;
    key_table[0x18] = KEY_F15;
    key_table[0x20] = KEY_F16;
    key_table[0x28] = KEY_F17;
    key_table[0x30] = KEY_F18;
    key_table[0x38] = KEY_F19;
    key_table[0x40] = KEY_F20;
    key_table[0x48] = KEY_F21;
    key_table[0x50] = KEY_F22;
    key_table[0x57] = KEY_F23;
    key_table[0x5F] = KEY_F24;

    // Navigation cluster
    key_table[0x67] = KEY_INSERT;
    key_table[0x6E] = KEY_HOME;
    key_table[0x6F] = KEY_PAGE_UP;
    key_table[0x64] = KEY_DELETE;
    key_table[0x65] = KEY_END;
    key_table[0x6D] = KEY_PAGE_DOWN;

    key_table[0x63] = KEY_UP_ARROW;
    key_table[0x61] = KEY_LEFT_ARROW;
    key_table[0x62] = KEY_DOWN_ARROW;
    key_table[0x6A] = KEY_RIGHT_ARROW;
    key_table[0x60] = KEY_DOWN_ARROW;

    // Keypad
    key_table[0x76] = KEY_NUM_LOCK;
    key_table[0x77] = KEYPAD_DIVIDE;
    key_table[0x7E] = KEYPAD_MULTIPLY;
    key_table[0x84] = KEYPAD_SUBTRACT;
    key_table[0x6C] = KEYPAD_7;
    key_table[0x75] = KEYPAD_8;
    key_table[0x7D] = KEYPAD_9;
    key_table[0x7C] = KEYPAD_ADD;
    key_table[0x6B] = KEYPAD_4;
    key_table[0x73] = KEYPAD_5;
    key_table[0x74] = KEYPAD_6;
    key_table[0x7B] = KEYPAD_ADD;
    key_table[0x69] = KEYPAD_1;
    key_table[0x72] = KEYPAD_2;
    key_table[0x7A] = KEYPAD_3;
    key_table[0x79] = KEYPAD_ENTER;
    key_table[0x70] = KEYPAD_0;
    key_table[0x71] = KEYPAD_DOT;

    // Left functions
    key_table[0x05] = KEY_ESC;
    key_table[0x06] = KEY_PRINT;
    key_table[0x04] = KEY_SCROLL_LOCK;
    key_table[0x0C] = KEY_PAUSE;
   // key_table[0x03] = KEY_;
   // key_table[0x0B] = KEY_;
   // key_table[0x83] = KEY_;
   // key_table[0x0A] = KEY_;
    key_table[0x01] = KEY_LEFT_GUI;
    key_table[0x09] = KEY_MENU;
}

#endif
