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

#include "Panel.h"

void Panel::begin() {
    buttons.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADR, true, false)) Serial.println("Pantalla no iniciada correctamente.");
    display.display();
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

void Panel::displayUpdate(const bool ctlMode,const float &leftVel,const float &rightVel,const float &dxlRPM) {
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);             // Start at top-left corner
    switch (currentMenu) { 
        case 0:
            display.println(F("Control:"));
            if (ctlMode) display.println(F("RC"));
            else display.println(F("Serial"));
            break;

        case 1:
            display.println(F("Left vel:"));
            display.print(leftVel);
            break;

        case 2:
            display.println(F("Right vel:"));
            display.print(rightVel);
            break;

        case 3:
            display.println(F("DXL RPM:"));
            display.print(dxlRPM);
            break;
    }
    display.display();
}
