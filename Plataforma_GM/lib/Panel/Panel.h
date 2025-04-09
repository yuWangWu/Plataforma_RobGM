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

#ifndef ADAFRUIT_SSD1306_H
#define ADAFRUIT_SSD1306_H
    #include "Adafruit_SSD1306.h"
#endif

#ifndef BUTTON_PAD_H
#define BUTTON_PAD_H
    #include "buttonPad.h"
#endif

#define I2C_SDA         16
#define I2C_SCK         4

#define OLED_WIDTH      128
#define OLED_HEIGHT     64
#define OLED_ADR        0x3C

#define MENU_QUANTITY   3       // = NUMBER OF MENUS - 1

class Panel {
private:
    buttonPad buttons;
    // enum 
    uint8_t currentMenu, maxMenu;
    Adafruit_SSD1306 display;

public:
    Panel(TwoWire &i2cBus) : currentMenu(0), maxMenu(MENU_QUANTITY), display(OLED_WIDTH, OLED_HEIGHT, &i2cBus, -1) {};
    void begin();

    // Display management
    void menuNext();
    void menuPrev();
    // sin const en datos basicos
    void displayUpdate(const bool ctlMode,const float &leftVel,const  float &rightVel,const  float &dxlRPM);

    // Button management
    void resetButton0() { buttons.setStateButton0(false); }
    void resetButton1() { buttons.setStateButton1(false); }
    void resetButton2() { buttons.setStateButton2(false); }
    void resetButton3() { buttons.setStateButton3(false); }

    bool getButton0() { return buttons.getStateButton0(); }
    bool getButton1() { return buttons.getStateButton1(); }
    bool getButton2() { return buttons.getStateButton2(); }
    bool getButton3() { return buttons.getStateButton3(); }
};