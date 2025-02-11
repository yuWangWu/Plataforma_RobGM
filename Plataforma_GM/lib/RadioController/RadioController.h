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

#define CH1PIN  36
#define CH2PIN  39
#define CH3PIN  34
#define CH4PIN  35
#define CH5PIN  33
#define CH6PIN  32

class RadioController {
private:
    unsigned long ch1Initial{}, ch1End{}, ch2End{}, ch3End{}, ch4End{}, ch5End{}, ch6End{};
    unsigned long ch1Value{}, ch2Value{}, ch3Value{};
    bool ch4Value{}, ch5Value{}, ch6Value{};

    void IRAM_ATTR ch1INTRR();
    void IRAM_ATTR ch2INTRR();
    void IRAM_ATTR ch3INTRR();
    void IRAM_ATTR ch4INTRR();
    void IRAM_ATTR ch5INTRR();
    void IRAM_ATTR ch6INTRR();
    
public:
    void begin();

    // Getters
    int getCH1Value() { return ch1Value; }
    int getCH2Value() { return ch2Value; }
    int getCH3Value() { return ch3Value; }
    bool getCH4Value() { return ch4Value; }
    bool getCH5Value() { return ch5Value; }
    bool getCH6Value() { return ch6Value; }
};



