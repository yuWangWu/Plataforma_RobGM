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

#ifndef WIRE_H
#define WIRE_H
    #include "Wire.h"
#endif

#ifndef ADAFRUIT_SSD1306_H
#define ADAFRUIT_SSD1306_H
    #include "Adafruit_SSD1306.h"
#endif

#ifndef STRING_H
#define STRING_H
    #include "string"
#endif

class Screen {
private: 
    uint8_t address;
    Adafruit_SSD1306 OLED;

public:
    Screen(uint8_t _w, uint8_t _h, uint8_t _adr) : OLED(_w, _h, &Wire, -1), address(_adr) {}
    void begin();

    void titleAndBottom(std::string title, std::string bottom);
    void titleAndBottom(std::string title, uint8_t bottom);
    
    void resetScreen();
    void titlePreset();
    void bottomPreset();
};