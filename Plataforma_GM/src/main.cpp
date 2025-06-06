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

#ifndef ARDUINO_H
#define ARDUINO_H
  #include <Arduino.h>
#endif

#ifndef WIRE_H
#define WIRE_H
  #include <Wire.h>
#endif

#ifndef RADIO_CONTROLLER_H
#define RADIO_CONTROLLER_H
  #include <RadioController.h>
#endif

#ifndef PANEL_H
#define PANEL_H
  #include <Panel.h>
#endif

#ifndef ROBOCLAW_H
#define ROBOCLAW_H
  #include "RoboClaw.h"
#endif

#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H
  #include "Dynamixel2Arduino.h"
#endif

// Parameters and pins
#define HB_TIM_CH       1
#define HB_TIM_DIV      40
#define HB_LED1         12
#define HB_LED2         14

#define RBCLW_BAUDRATE  115200
#define RBCLW_RXPIN     15
#define RBCLW_TXPIN     13
#define RBCLW1_DIR      135
#define RBCLW2_DIR      128

#define DXL_BAUDRATE    1000000
#define DXL_RX          23
#define DXL_TX          22
#define DXL_DIR         21
#define DXL_ID          3

// Check battery lvl timer (necessary to not overwhelm rbclw)
hw_timer_t *battCheckerTim = NULL;
volatile bool battFlag{false};
void IRAM_ATTR checkBatt() {
  battFlag = true;
}

RadioController rc;
Panel frontPanel;
RoboClaw roboclaw1(&Serial2, 10000);
RoboClaw roboclaw2(&Serial2, 10000);
Dynamixel2Arduino servo(Serial1, DXL_DIR);

ctlMode opMode;

int battLvl{};
float horizontal{}, vertical{}, servoRPM{};
float motorLeftSide{}, motorRightSide{};

void setup() {
  // Heartbeat
  pinMode(HB_LED1, OUTPUT);
  pinMode(HB_LED2, OUTPUT);
  digitalWrite(HB_LED1, 1);
  battCheckerTim = timerBegin(1, 800, true);
  timerAttachInterrupt(battCheckerTim, &checkBatt, true);
  timerAlarmWrite(battCheckerTim, 1000000, true);
  timerAlarmEnable(battCheckerTim);

  // Comunications
  Serial.begin(115200);
  Serial1.begin(DXL_BAUDRATE, SERIAL_8N1, DXL_RX, DXL_TX);
  Serial2.begin(RBCLW_BAUDRATE, SERIAL_8N1, RBCLW_RXPIN, RBCLW_TXPIN);
  Wire.begin(I2C_SDA, I2C_SCK);

  Serial.println("Communications active");

  // Components
  rc.begin();
  frontPanel.begin();

  // ToDo: Physical component check goes here...

  servo.begin(1000000);
  servo.setPortProtocolVersion(2.0);
  servo.ping(DXL_ID);
  servo.torqueOff(DXL_ID);
  servo.setOperatingMode(DXL_ID, OP_VELOCITY);
  servo.torqueOn(DXL_ID);
}

void loop() {
  digitalWrite(HB_LED1, !digitalRead(HB_LED1));
  digitalWrite(HB_LED2, !digitalRead(HB_LED1));

  // Front interface button actions
  if (frontPanel.getButton0()) { 
    Serial.println("Event on Button 0");
    frontPanel.menuPrev();
    frontPanel.resetButton0();
  }
  if (frontPanel.getButton1()) { 
    Serial.println("Event on Button 1");
    frontPanel.menuNext();
    frontPanel.resetButton1();
  }

  opMode = rc.getCH4Value() ? RC_CONTROL : SERIAL_CONTROL;
  if (battFlag) {
    battLvl = roboclaw1.ReadMainBatteryVoltage(RBCLW1_DIR);
    battFlag = false;
  }

  // Front interface screen update
  frontPanel.displayUpdate(opMode, std::to_string(horizontal), std::to_string(vertical), std::to_string(servoRPM), std::to_string(battLvl));

  // Movement
  if (opMode == RC_CONTROL) {
    horizontal = map(rc.getCH1Value(), 700, 1800, 100, -100);
    vertical = map(rc.getCH2Value(), 700, 1800, -100, 100);
    servoRPM = map(rc.getCH3Value(), 1100, 1900, 0, 30);

    motorLeftSide = (horizontal + vertical) / 200 * 127;
    motorRightSide = (horizontal - vertical) / 200 * 127;

    if (motorLeftSide > 0) {
      roboclaw1.ForwardM2(RBCLW1_DIR, motorLeftSide);
      roboclaw2.ForwardM1(RBCLW2_DIR, motorLeftSide);
    } else {
      roboclaw1.BackwardM2(RBCLW1_DIR, -motorLeftSide);
      roboclaw2.BackwardM1(RBCLW2_DIR, -motorLeftSide);
    }
    if (motorRightSide > 0) {
      roboclaw1.ForwardM1(RBCLW1_DIR, motorRightSide);
      roboclaw2.ForwardM2(RBCLW2_DIR, motorRightSide);
    } else {
      roboclaw1.BackwardM1(RBCLW1_DIR, -motorRightSide);
      roboclaw2.BackwardM2(RBCLW2_DIR, -motorRightSide);
    }

    servo.setGoalVelocity(DXL_ID, servoRPM, UNIT_RPM);
  } 
  else {
    roboclaw1.ForwardM1(RBCLW1_DIR, 0);
    roboclaw1.ForwardM2(RBCLW1_DIR, 0);
    roboclaw2.ForwardM1(RBCLW2_DIR, 0);
    roboclaw2.ForwardM2(RBCLW2_DIR, 0);
    servo.setGoalVelocity(DXL_ID, 0, UNIT_RPM);
  }
}

// lectura de encoders
// empaquetamiento de los datos 
// panel: autogestion de botones
// cargador de bateria
// condensadores roboclaw
// cambiar iconos pantalla dinamicamente

// referencia rosa
