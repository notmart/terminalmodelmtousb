#ifndef MACROTABLE_H
#define MACROTABLE_H

#include "HID-Project.h"

//static void* macro_table[256];

static void (*macro_table[256])();

void macro_compose_key()
{
    BootKeyboard.press(KEY_RIGHT_ALT);
    BootKeyboard.write(KEY_MENU);
    BootKeyboard.release(KEY_RIGHT_ALT);
}

void macro_1()
{
    BootKeyboard.println("git pull --rebase");
}

void macro_2()
{
    
}

void macro_3()
{
    
}

void macro_4()
{
    
}

void macro_5()
{
    
}

void macro_6()
{
    
}

void macro_7()
{
    
}

void macro_8()
{
    
}

void macro_9()
{
    
}


void setup_macro_table()
{
    //default to zero which won't send anything
    for (int i = 0; i < 256; ++i) {
        macro_table[i] = nullptr;
    }

    // Numer row
    macro_table[0xE] = nullptr;
    macro_table[0x16] = nullptr;
    macro_table[0x1E] = nullptr;
    macro_table[0x26] = nullptr;
    macro_table[0x25] = nullptr;
    macro_table[0x2E] = nullptr;
    macro_table[0x36] = nullptr;
    macro_table[0x3D] = nullptr;
    macro_table[0x3E] = nullptr;
    macro_table[0x46] = nullptr;
    macro_table[0x45] = nullptr;
    macro_table[0x4E] = nullptr;
    macro_table[0x55] = nullptr;

    // Q ROW
    macro_table[0x15] = nullptr;
    macro_table[0x1D] = nullptr;
    macro_table[0x24] = nullptr;
    macro_table[0x2D] = nullptr;
    macro_table[0x2C] = nullptr;
    macro_table[0x35] = nullptr;
    macro_table[0x3C] = nullptr;
    macro_table[0x43] = nullptr;
    macro_table[0x44] = nullptr;
    macro_table[0x4d] = nullptr;
    macro_table[0x54] = nullptr;
    macro_table[0x5B] = nullptr;

    macro_table[0x1C] = nullptr;
    macro_table[0x1B] = nullptr;
    macro_table[0x23] = nullptr;
    macro_table[0x2B] = nullptr;
    macro_table[0x34] = nullptr;
    macro_table[0x33] = nullptr;
    macro_table[0x3B] = nullptr;
    macro_table[0x42] = nullptr;
    macro_table[0x4B] = nullptr;
    macro_table[0x4C] = nullptr;
    macro_table[0x52] = nullptr;
    macro_table[0x53] = nullptr;

    macro_table[0x13] = nullptr;
    macro_table[0x1A] = nullptr;
    macro_table[0x22] = nullptr;
    macro_table[0x21] = nullptr;
    macro_table[0x2A] = nullptr;
    macro_table[0x32] = nullptr;
    macro_table[0x31] = nullptr;
    macro_table[0x3A] = nullptr;
    macro_table[0x41] = nullptr;
    macro_table[0x49] = nullptr;
    macro_table[0x4A] = nullptr;

    // Command keys
    macro_table[0x0D] = nullptr;
    macro_table[0x14] = nullptr;
    macro_table[0x12] = nullptr;
    macro_table[0x11] = nullptr;
    macro_table[0x19] = nullptr;
    macro_table[0x29] = nullptr;
    macro_table[0x39] = nullptr;
    macro_table[0x58] = nullptr;
    macro_table[0x59] = nullptr;
    macro_table[0x5a] = nullptr;
    macro_table[0x66] = nullptr;

    // Function rows
    macro_table[0x07] = nullptr;
    macro_table[0x0F] = nullptr;
    macro_table[0x17] = nullptr;
    macro_table[0x1F] = nullptr;
    macro_table[0x27] = nullptr;
    macro_table[0x2F] = nullptr;
    macro_table[0x37] = nullptr;
    macro_table[0x3F] = nullptr;
    macro_table[0x47] = nullptr;
    macro_table[0x4F] = nullptr;
    macro_table[0x56] = nullptr;
    macro_table[0x5E] = nullptr;

    macro_table[0x08] = nullptr;
    macro_table[0x10] = nullptr;
    macro_table[0x18] = nullptr;
    macro_table[0x20] = nullptr;
    macro_table[0x28] = nullptr;
    macro_table[0x30] = nullptr;
    macro_table[0x38] = nullptr;
    macro_table[0x40] = nullptr;
    macro_table[0x48] = nullptr;
    macro_table[0x50] = nullptr;
    macro_table[0x57] = nullptr;
    macro_table[0x5F] = nullptr;

    // Navigation cluster
    macro_table[0x67] = nullptr;
    macro_table[0x6E] = nullptr;
    macro_table[0x6F] = nullptr;
    macro_table[0x64] = nullptr;
    macro_table[0x65] = nullptr;
    macro_table[0x6D] = nullptr;

    macro_table[0x63] = nullptr;
    macro_table[0x61] = nullptr;
    macro_table[0x62] = nullptr;
    macro_table[0x6A] = nullptr;
    macro_table[0x60] = nullptr;

    // Keypad
    macro_table[0x76] = nullptr;
    macro_table[0x77] = nullptr;
    macro_table[0x7E] = nullptr;
    macro_table[0x84] = nullptr;
    macro_table[0x6C] = nullptr;
    macro_table[0x75] = nullptr;
    macro_table[0x7D] = nullptr;
    macro_table[0x7C] = nullptr;
    macro_table[0x6B] = nullptr;
    macro_table[0x73] = nullptr;
    macro_table[0x74] = nullptr;
    macro_table[0x7B] = nullptr;
    macro_table[0x69] = nullptr;
    macro_table[0x72] = nullptr;
    macro_table[0x7A] = nullptr;
    macro_table[0x79] = nullptr;
    macro_table[0x70] = nullptr;
    macro_table[0x71] = nullptr;

    // Left functions
    macro_table[0x05] = nullptr;
    macro_table[0x06] = nullptr;
    macro_table[0x04] = nullptr;
    macro_table[0x0C] = nullptr;
    macro_table[0x03] = macro_3;
    macro_table[0x0B] = macro_2;
    macro_table[0x83] = macro_1;
    macro_table[0x0A] = macro_compose_key;
    macro_table[0x01] = nullptr;
    macro_table[0x09] = nullptr;
}

#endif
