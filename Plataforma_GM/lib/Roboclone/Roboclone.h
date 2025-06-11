#ifndef ROBOCLONE_H
    #define ROBOCLONE_H
#endif

#define MAXRETRIES 2

#include <Stream.h>
#include <HardwareSerial.h>

class RoboClone {
private:
    uint8_t address;
    uint16_t crc;
    uint32_t timeout;

    HardwareSerial *hserial;

    enum {
        M1FORWARD = 0,
        M1BACKWARD = 1,
        SETMINMB = 2,
        SETMAXMB = 3,
        M2FORWARD = 4,
        M2BACKWARD = 5,
        M17BIT = 6,
        M27BIT = 7,
        MIXEDFORWARD = 8,
        MIXEDBACKWARD = 9,
        MIXEDRIGHT = 10,
        MIXEDLEFT = 11,
        MIXEDFB = 12,
        MIXEDLR = 13,
        GETM1ENC = 16,
        GETM2ENC = 17,
        GETM1SPEED = 18,
        GETM2SPEED = 19,
        RESETENC = 20,
        GETVERSION = 21,
        SETM1ENCCOUNT = 22,
        SETM2ENCCOUNT = 23,
        GETMBATT = 24,
        GETLBATT = 25,
        SETMINLB = 26,
        SETMAXLB = 27,
        SETM1PID = 28,
        SETM2PID = 29,
        GETM1ISPEED = 30,
        GETM2ISPEED = 31,
        M1DUTY = 32,
        M2DUTY = 33,
        MIXEDDUTY = 34,
        M1SPEED = 35,
        M2SPEED = 36,
        MIXEDSPEED = 37,
        M1SPEEDACCEL = 38,
        M2SPEEDACCEL = 39,
        MIXEDSPEEDACCEL = 40,
        M1SPEEDDIST = 41,
        M2SPEEDDIST = 42,
        MIXEDSPEEDDIST = 43,
        M1SPEEDACCELDIST = 44,
        M2SPEEDACCELDIST = 45,
        MIXEDSPEEDACCELDIST = 46,
        GETBUFFERS = 47,
        GETPWMS = 48,
        GETCURRENTS = 49,
        MIXEDSPEED2ACCEL = 50,
        MIXEDSPEED2ACCELDIST = 51,
        M1DUTYACCEL = 52,
        M2DUTYACCEL = 53,
        MIXEDDUTYACCEL = 54,
        READM1PID = 55,
        READM2PID = 56,
        SETMAINVOLTAGES = 57,
        SETLOGICVOLTAGES = 58,
        GETMINMAXMAINVOLTAGES = 59,
        GETMINMAXLOGICVOLTAGES = 60,
        SETM1POSPID = 61,
        SETM2POSPID = 62,
        READM1POSPID = 63,
        READM2POSPID = 64,
        M1SPEEDACCELDECCELPOS = 65,
        M2SPEEDACCELDECCELPOS = 66,
        MIXEDSPEEDACCELDECCELPOS = 67,
        SETM1DEFAULTACCEL = 68,
        SETM2DEFAULTACCEL = 69,
        SETPINFUNCTIONS = 74,
        GETPINFUNCTIONS = 75,
        SETDEADBAND	= 76,
        GETDEADBAND	= 77,
        GETENCODERS = 78,
        GETISPEEDS = 79,
        RESTOREDEFAULTS = 80,
        GETTEMP = 82,
        GETTEMP2 = 83,	//Only valid on some models
        GETERROR = 90,
        GETENCODERMODE = 91,
        SETM1ENCODERMODE = 92,
        SETM2ENCODERMODE = 93,
        WRITENVM = 94,
        READNVM = 95,	//Reloads values from Flash into Ram
        SETCONFIG = 98,
        GETCONFIG = 99,
        SETM1MAXCURRENT = 133,
        SETM2MAXCURRENT = 134,
        GETM1MAXCURRENT = 135,
        GETM2MAXCURRENT = 136,
        SETPWMMODE = 148,
        GETPWMMODE = 149,
        FLAGBOOTLOADER = 255};	//Only available via USB communications

    enum {
		ERROR_NONE			= 0x000000,
		ERROR_ESTOP			= 0x000001,	//Error: E-Stop active
		ERROR_TEMP			= 0x000002,	//Error: Temperature Sensor 1 >=100c
		ERROR_TEMP2			= 0x000004,	//Error: Temperature Sensor 2 >=100C (available only on some models)
		ERROR_MBATHIGH		= 0x000008,	//Error: Main Battery Over Voltage
		ERROR_LBATHIGH		= 0x000010,	//Error: Logic Battery High Voltage
		ERROR_LBATLOW		= 0x000020,	//Error: Logic Battery Low Voltage
		ERROR_FAULTM1		= 0x000040,	//Error: Motor 1 Driver Fault (only on some models)
		ERROR_FAULTM2		= 0x000080,	//Error: Motor 2 Driver Fault (only on some models)
		ERROR_SPEED1		= 0x000100,	//Error: Motor 1 Speed Error Limit
		ERROR_SPEED2		= 0x000200,	//Error: Motor 2 Speed Error Limit
		ERROR_POS1			= 0x000400,	//Error: Motor 1 Position Error Limit
		ERROR_POS2			= 0x000800,	//Error: MOtor2 Position Error Limit
		WARN_OVERCURRENTM1	= 0x010000, //Warning: Motor 1 Current Limited
		WARN_OVERCURRENTM2	= 0x020000, //Warning: Motor 2 CUrrent Limited
		WARN_MBATHIGH		= 0x040000, //Warning: Main Battery Voltage High
		WARN_MBATLOW		= 0x080000, //Warning: Main Battery Low Voltage
		WARN_TEMP			= 0x100000, //Warning: Temperaure Sensor 1 >=85C
		WARN_TEMP2			= 0x200000, //Warning: Temperature Sensor 2 >=85C (available only on some models)
		WARN_S4				= 0x400000, //Warning: Motor 1 Home/Limit Signal
		WARN_S5				= 0x800000, //Warning: Motor 2 Home/Limit Signal
	};

    void crc_update(uint8_t data);
    int read();

public:
    RoboClone(HardwareSerial *_hserial, uint8_t _adr, uint32_t _tout) {
        hserial = _hserial;
        address = _adr;
        timeout = _tout;
    };
    ~RoboClone() {};

    bool ResetEncoders();
    bool ReadEncoders(uint32_t *enc1, uint32_t *enc2);

    uint16_t ReadMainBatteryVoltage();

    bool ForwardM1(uint8_t value);
    bool BackwardM1(uint8_t value);
    bool ForwardM2(uint8_t value);
    bool BackwardM2(uint8_t value);
};
