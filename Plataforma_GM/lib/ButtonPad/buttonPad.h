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

#define BT0PIN          10
#define BT1PIN          11
#define BT2PIN          12
#define BT3PIN          13

class buttonPad {
private:
    bool stateButton0{false}, stateButton1{false}, stateButton2{false}, stateButton3{false};

    // Button interrupts
    void IRAM_ATTR bt0INTRR();
    void IRAM_ATTR bt1INTRR();
    void IRAM_ATTR bt2INTRR();
    void IRAM_ATTR bt3INTRR();

public:
    void begin();

    // Getters
    bool getStateButton0() { return stateButton0; }
    bool getStateButton1() { return stateButton1; }
    bool getStateButton2() { return stateButton2; }
    bool getStateButton3() { return stateButton3; }
};