/*
Copyright (c) 2024 Yu Wang Wu

Permission is hereby granted, free of charge, to any 
person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the 
Software without restriction, including without 
limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the 
following conditions:

The above copyright notice and this permission 
notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY 
OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT 
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef ARDUINO_H
#define ARDUINO_H
    #include "Arduino.h"
#endif

#ifndef BUTTON_PAD_H
#define BUTTON_PAD_H
    #include "buttonPad.h"
#endif

#ifndef SCREEN_H
#define SCREEN_H
    #include "Screen.h"
#endif

#define I2C_SDA         22
#define I2C_SCK         21

#define OLED_WIDTH      128
#define OLED_HEIGHT     32
#define OLED_ADR        0x3C

#define MENU_QUANTITY   3       // = NUMBER OF MENUS - 1

class Panel {
private:
    buttonPad buttons;
    uint8_t currentMenu, maxMenu;
    Screen oled{OLED_WIDTH, OLED_HEIGHT, OLED_ADR};

public:
    Panel() : currentMenu(0), maxMenu(MENU_QUANTITY) {};

    void begin();

    void menuNext();
    void menuPrev();
    void displayUpdate(bool ctlMode, float &leftVel, float &rightVel, float &dxlRPM);

    bool getButton0() { return buttons.getStateButton0(); };
    bool getButton1() { return buttons.getStateButton1(); };
    bool getButton2() { return buttons.getStateButton2(); };
    bool getButton3() { return buttons.getStateButton3(); };
};