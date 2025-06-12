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

#include <stdio.h>
#include "Panel.h"

void Panel::begin() {
    display.begin();
    display.firstPage();

    display.setFont(u8g2_font_6x13_tf);

    display.drawLine(99, 1, 99, 11);
    display.drawBitmap(32, 23, 2, 35, robot_left);
    display.drawBitmap(87, 23, 2, 35, robot_right);

    display.drawBitmap(0, 0, 4, 13, battery);
    display.drawStr(57, 12, "V");
    //u8g2.drawBitmap(0, 15, 4, 13, battery_warning);
    display.drawBitmap(67, 0, 4, 13, usb_cable);
    //u8g2.drawBitmap(81, 15, 2, 13, rc_symbol);
    display.drawBitmap(103, 0, 2, 13, chip);
    display.drawBitmap(119, 0, 2, 13, question_mark);

    display.sendBuffer();
    display.refreshDisplay();
    //u8g2.drawBitmap(119, 15, 2, 13, tick_mark);    
    // if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADR, true, false)) Serial.println("Pantalla no iniciada correctamente.");
    // display.display();
}

void Panel::menuNext() {
    Serial.println("Current menu: ");
    Serial.println(currentMenu);

    if (currentMenu < maxMenu) currentMenu++;
    else currentMenu = 0;
    Serial.println(currentMenu);
}

void Panel::menuPrev() {
    Serial.println("Current menu: ");
    Serial.println(currentMenu);
    
    if (currentMenu > 0) currentMenu--;
    else currentMenu = maxMenu;
    Serial.println(currentMenu);
}

void Panel::displayUpdate(ctlMode opMode, std::string leftVel, std::string rightVel, std::string dxlRPM, std::string battLvl,
                            std::string m1enc, std::string m2enc, std::string m3enc, std::string m4enc) {
    if (opMode == RC_CONTROL) {
        display.setDrawColor(0);
        display.drawBox(67, 0, 81, 13);
        display.setDrawColor(1);
        display.drawBitmap(81, 0, 2, 13, rc_symbol);
    } else {
        display.drawBitmap(67, 0, 4, 13, usb_cable);
    }

    updateEncoders(m1enc, m2enc, m3enc, m4enc);
    updateBatt(battLvl);
    updateLV(leftVel);
    updateRV(rightVel);
    updateDXL(dxlRPM);

    display.sendBuffer();
    display.refreshDisplay();
}

// full of magic numbers i know, i know... 
void Panel::updateEncoders(std::string m1enc, std::string m2enc, std::string m3enc, std::string m4enc) {
    display.setDrawColor(0);
    display.drawBox(0, 15, 30, 13);
    display.drawBox(0, 50, 30, 13);
    display.drawBox(98, 15, 30, 13);
    display.drawBox(98, 50, 30, 13);
    display.setDrawColor(1);

    m1enc.resize(6);
    m2enc.resize(6);
    m3enc.resize(6);
    m4enc.resize(6);
    display.drawStr(0, 28, m1enc.c_str());
    display.drawStr(0, 63, m2enc.c_str());
    display.drawStr(98, 28, m3enc.c_str());
    display.drawStr(98, 63, m4enc.c_str());
}

void Panel::updateLV(std::string leftVel) {
    display.setDrawColor(0);
    display.drawBox(0, 33, 30, 13);
    display.setDrawColor(1);

    leftVel.resize(5);
    display.drawStr(0, 45, leftVel.c_str());
}

void Panel::updateRV(std::string rightVel) {
    display.setDrawColor(0);
    display.drawBox(98, 33, 30, 13);
    display.setDrawColor(1);

    rightVel.resize(5);
    display.drawStr(98, 45, rightVel.c_str());
}

void Panel::updateDXL(std::string DXLval) {
    display.setDrawColor(0);
    display.drawBox(46, 33, 36, 13);
    display.setDrawColor(1);

    DXLval.resize(6);
    display.drawStr(46, 45, DXLval.c_str());
}

void Panel::updateBatt(std::string BattVal) {
    display.setDrawColor(0);
    display.drawBox(33, 0, 24, 13);
    display.setDrawColor(1);

    BattVal.resize(4);
    display.drawStr(33, 12, BattVal.c_str());
}
