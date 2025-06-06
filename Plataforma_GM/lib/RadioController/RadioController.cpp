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

#include "RadioController.h"

#ifndef FUNCTIONAL_INTERRUPT_H
#define FUNCTIONAL_INTERRUPT_H
    #include "FunctionalInterrupt.h"
#endif

void RadioController::begin() {
    pinMode(CH1PIN, INPUT_PULLUP);
    pinMode(CH2PIN, INPUT_PULLUP);
    pinMode(CH3PIN, INPUT_PULLUP);
    pinMode(CH4PIN, INPUT_PULLUP);
    pinMode(CH5PIN, INPUT_PULLUP);
    pinMode(CH6PIN, INPUT_PULLUP);

    ch1Value = 0; ch2Value = 0; ch3Value = 0;
    ch4Value = false; ch5Value = false; ch6Value = false;

    attachInterrupt(digitalPinToInterrupt(CH1PIN), std::bind(&RadioController::ch1INTRR, this), CHANGE);
    attachInterrupt(digitalPinToInterrupt(CH2PIN), std::bind(&RadioController::ch2INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH3PIN), std::bind(&RadioController::ch3INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH4PIN), std::bind(&RadioController::ch4INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH5PIN), std::bind(&RadioController::ch5INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH6PIN), std::bind(&RadioController::ch6INTRR, this), FALLING);
}

void IRAM_ATTR RadioController::ch1INTRR() {
    unsigned long actual = micros();
    if ((actual - ch1Initial) > chMaxOn) {
        ch1Initial = actual;
    } else {
        ch1End = actual;
        ch1Value = ch1End - ch1Initial;
    }
}

void IRAM_ATTR RadioController::ch2INTRR() {
    ch2End = micros();
    ch2Value = ch2End - ch1End - chDelay;
}

void IRAM_ATTR RadioController::ch3INTRR() {
    ch3End = micros();
    ch3Value = ch3End - ch2End - chDelay;
}

void IRAM_ATTR RadioController::ch4INTRR() {
    ch4End = micros();
    ch4Value = (ch4End - ch3End - chDelay) < chDigitalThreshold ? false : true;
}

void IRAM_ATTR RadioController::ch5INTRR() {
    ch5End = micros();
    ch5Value = (ch5End - ch4End - chDelay) < chDigitalThreshold ? false : true;
}

void IRAM_ATTR RadioController::ch6INTRR() {
    ch6End = micros();
    ch6Value = (ch6End - ch5End - chDelay) < chDigitalThreshold ? false : true;
}
