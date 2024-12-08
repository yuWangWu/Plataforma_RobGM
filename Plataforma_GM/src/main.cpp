#include <Arduino.h>
#include <RadioController.h>
#include "RoboClaw.h"
#include "Dynamixel2Arduino.h"

#define RBCLW_BAUDRATE  115200
#define RBCLW_RXPIN     16
#define RBCLW_TXPIN     17
#define RBCLW1_DIR      135
#define RBCLW2_DIR      128

#define DXL_BAUDRATE    1000000
#define DXL_RX          18
#define DXL_TX          19
#define DXL_DIR         22
#define DXL_ID          3

RadioController RC;
RoboClaw roboclaw1(&Serial2, 10000);
RoboClaw roboclaw2(&Serial2, 10000);
Dynamixel2Arduino servo(Serial1, DXL_DIR);

float direccion{}, sentido{}, rpmServo{};
float motorIzq{}, motorDer{};

void setup() {
  Serial.begin(115200);
  Serial1.begin(DXL_BAUDRATE, SERIAL_8N1, DXL_RX, DXL_TX);
  Serial2.begin(RBCLW_BAUDRATE, SERIAL_8N1, RBCLW_RXPIN, RBCLW_TXPIN);

  RC.begin();

  servo.begin(1000000);
  servo.setPortProtocolVersion(2.0);
  servo.ping(DXL_ID);
  servo.torqueOff(DXL_ID);
  servo.setOperatingMode(DXL_ID, OP_VELOCITY);
  servo.torqueOn(DXL_ID);
}

void loop() {
  if (RC.getCH5Value()) {
    direccion = map(RC.getCH1Value(), 700, 1800, 100, -100);
    sentido = map(RC.getCH2Value(), 700, 1800, -100, 100);
    rpmServo = map(RC.getCH3Value(), 1100, 1900, 0, 30);

    motorIzq = (direccion + sentido) / 200 * 127;
    motorDer = (direccion - sentido) / 200 * 127;

    if (motorIzq > 0) roboclaw1.ForwardM2(RBCLW1_DIR, motorIzq);
    else roboclaw1.BackwardM2(RBCLW1_DIR, -motorIzq);
    if (motorDer > 0) roboclaw1.ForwardM1(RBCLW1_DIR, motorDer);
    else roboclaw1.BackwardM1(RBCLW1_DIR, -motorDer);
    if (motorIzq > 0) roboclaw2.ForwardM1(RBCLW2_DIR, motorIzq);
    else roboclaw2.BackwardM1(RBCLW2_DIR, -motorIzq);
    if (motorDer > 0) roboclaw2.ForwardM2(RBCLW2_DIR, motorDer);
    else roboclaw2.BackwardM2(RBCLW2_DIR, -motorDer);

    servo.setGoalVelocity(DXL_ID, rpmServo, UNIT_RPM);
  } 
  else {
    roboclaw1.ForwardM1(RBCLW1_DIR, 0);
    roboclaw1.ForwardM2(RBCLW1_DIR, 0);
    roboclaw2.ForwardM1(RBCLW2_DIR, 0);
    roboclaw2.ForwardM2(RBCLW2_DIR, 0);
    servo.setGoalVelocity(DXL_ID, 0, UNIT_RPM);
  }
}
