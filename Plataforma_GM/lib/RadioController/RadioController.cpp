#include "RadioController.h"
#include "FunctionalInterrupt.h"

void RadioController::begin() {
    pinMode(CH1PIN, INPUT_PULLUP);
    pinMode(CH2PIN, INPUT_PULLUP);
    pinMode(CH3PIN, INPUT_PULLUP);
    pinMode(CH4PIN, INPUT_PULLUP);
    pinMode(CH5PIN, INPUT_PULLUP);
    pinMode(CH6PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(CH1PIN), std::bind(&RadioController::ch1INTRR, this), CHANGE);
    attachInterrupt(digitalPinToInterrupt(CH2PIN), std::bind(&RadioController::ch2INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH3PIN), std::bind(&RadioController::ch3INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH4PIN), std::bind(&RadioController::ch4INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH5PIN), std::bind(&RadioController::ch5INTRR, this), FALLING);
    attachInterrupt(digitalPinToInterrupt(CH6PIN), std::bind(&RadioController::ch6INTRR, this), FALLING);
}

void IRAM_ATTR RadioController::ch1INTRR() {
    unsigned long actual = micros();
    if ((actual - ch1Initial) > 3500) {
        ch1Initial = actual;
    } else {
        ch1End = actual;
        ch1Value = ch1End - ch1Initial;
    }
}

void IRAM_ATTR RadioController::ch2INTRR() {
    ch2End = micros();
    ch2Value = ch2End - ch1End - 1;
}

void IRAM_ATTR RadioController::ch3INTRR() {
    ch3End = micros();
    ch3Value = ch3End - ch2End - 1;
}

void IRAM_ATTR RadioController::ch4INTRR() {
    ch4End = micros();
    ch4Value = (ch4End - ch3End - 1) < 1500 ? false : true;
}

void IRAM_ATTR RadioController::ch5INTRR() {
    ch5End = micros();
    ch5Value = (ch5End - ch4End - 1) < 1500 ? false : true;
}

void IRAM_ATTR RadioController::ch6INTRR() {
    ch6End = micros();
    ch6Value = (ch6End - ch5End - 1) < 1500 ? false : true;
}
