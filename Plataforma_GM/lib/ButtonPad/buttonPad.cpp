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

#include "buttonPad.h"

#ifndef FUNCTIONAL_INTERRUPT_H
#define FUNCTIONAL_INTERRUPT_H
    #include "FunctionalInterrupt.h"
#endif

void buttonPad::begin() {
    attachInterrupt(digitalPinToInterrupt(BT0PIN), std::bind(&buttonPad::bt0INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(BT1PIN), std::bind(&buttonPad::bt1INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(BT2PIN), std::bind(&buttonPad::bt2INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(BT3PIN), std::bind(&buttonPad::bt3INTRR, this), FALLING);
}

void IRAM_ATTR buttonPad::bt0INTRR() {
    stateButton0 = true;
}

void IRAM_ATTR buttonPad::bt1INTRR() {
    stateButton1 = true;
}

void IRAM_ATTR buttonPad::bt2INTRR() {
    stateButton2 = true;
}

void IRAM_ATTR buttonPad::bt3INTRR() {
    stateButton3 = true;
}
