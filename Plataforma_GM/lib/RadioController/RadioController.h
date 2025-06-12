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
#define CH5PIN  32
#define CH6PIN  33

class RadioController {
private:
    static const unsigned long chDelay = 1; // us
    static const unsigned long chMaxOn = 3500; // us
    static const unsigned long chDigitalThreshold = 1500; // us

    static const unsigned long ch1Min = 1000;
    static const unsigned long ch1Max = 2300;
    static const unsigned long ch2Min = 800;
    static const unsigned long ch2Max = 1900;
    static const unsigned long ch3Min = 1000;
    static const unsigned long ch3Max = 2100;
    static const unsigned long ch4Min = 900;
    static const unsigned long ch4Max = 2200;

    unsigned long ch1Value{}, ch2Value{}, ch3Value{}, ch4Value{};
    bool ch5Value{}, ch6Value{};
    unsigned long ch1Initial{}, ch1End{}, ch2End{}, ch3End{}, ch4End{}, ch5End{}, ch6End{};

    void IRAM_ATTR ch1INTRR();
    void IRAM_ATTR ch2INTRR();
    void IRAM_ATTR ch3INTRR();
    void IRAM_ATTR ch4INTRR();
    void IRAM_ATTR ch5INTRR();
    void IRAM_ATTR ch6INTRR();
    
public:
    void begin();

    // Getters
    unsigned long getCH1Value() { return ch1Value; }
    unsigned long getCH2Value() { return ch2Value; }
    unsigned long getCH3Value() { return ch3Value; }
    unsigned long getCH4Value() { return ch4Value; }
    bool getCH5Value() { return ch5Value; }
    bool getCH6Value() { return ch6Value; }
};



