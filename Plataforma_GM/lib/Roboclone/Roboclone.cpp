#include "Roboclone.h"

void RoboClone::crc_update(uint8_t data) {
    crc = crc ^ ((uint16_t) data << 8);
    for (int i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc <<= 1;
    }
}

int RoboClone::read() {
    uint32_t start = micros();

    while (!hserial->available()) {
        if ((micros() - start) >= timeout) 
            return -1;
    }

    return hserial->read();
}

// Set both CH encoders to 0
bool RoboClone::ResetEncoders() {
    uint8_t tries = MAXRETRIES;

    do {
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(RESETENC);
        hserial->write(RESETENC);

        hserial->write(crc >> 8);
        hserial->write(crc);

        if (read() == 0xff) 
            return true;
    } while (tries--);

    return false;
}

// Read and save encoder values to defined variables
bool RoboClone::ReadEncoders(uint32_t *enc1, uint32_t *enc2) {
    uint8_t tries = MAXRETRIES;
    int16_t inData;
    uint32_t valueEnc = 0;

    do {
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(GETENCODERS);
        hserial->write(GETENCODERS);

        inData = read();
        crc_update(inData);
        valueEnc = (uint32_t) inData << 24;

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc |= (uint32_t) inData << 16;
        } else { break; }

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc |= (uint32_t) inData << 8;
        } else { break; }

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc |= (uint32_t) inData;
        } else { break; }
        
        *enc1 = valueEnc;

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc = (uint32_t) inData << 24;
        } else { break; }

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc |= (uint32_t) inData << 16;
        } else { break; }

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc |= (uint32_t) inData << 8;
        } else { break; }

        if (inData != -1) {
            inData = read();
            crc_update(inData);
            valueEnc |= (uint32_t) inData;
        } else { break; }

        *enc2 = valueEnc;

        if (inData != -1) {
            uint16_t ccrc;
            inData = read();
            if (inData != -1) {
                ccrc = inData << 8;
                inData = read();
                if (inData != -1) {
                    ccrc |= inData;
                    return crc == ccrc;
                }
            }
        }
    } while (tries--);

    return true;
}

// Returns main battery voltage
uint16_t RoboClone::ReadMainBatteryVoltage() {
    uint8_t tries = MAXRETRIES;
    int16_t inData;
    uint16_t voltage = 0;

    do {
        hserial->flush();
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(GETMBATT);
        hserial->write(GETMBATT);

        inData = read();
        crc_update(inData);
        voltage = (uint16_t) inData << 8;
        if (inData != -1) {
            inData = read();
            crc_update(inData);
            voltage |= (uint16_t) inData;
        }

        if (inData != -1) {
            uint16_t ccrc;
            inData = read();
            if (inData != -1) {
                ccrc = inData << 8;
                inData = read();
                if (inData != -1) {
                    ccrc |= inData;
                    if (crc == ccrc) {
                        return voltage;
                    }
                }
            }
        }
    } while (tries--);

    return false;
}

bool RoboClone::ForwardM1(uint8_t value) {
    uint8_t tries = MAXRETRIES;

    do {
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(M1FORWARD);
        hserial->write(M1FORWARD);
        
        crc_update(value);
        hserial->write(value);

        hserial->write(crc >> 8);
        hserial->write(crc);

        if (read() == 0xff)
            return true;
    } while (tries--);

    return false;
}

bool RoboClone::BackwardM1(uint8_t value) {
    uint8_t tries = MAXRETRIES;

    do { 
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(M1BACKWARD);
        hserial->write(M1BACKWARD);
        
        crc_update(value);
        hserial->write(value);

        hserial->write(crc >> 8);
        hserial->write(crc);

        if (read() == 0xff)
            return true;
    } while (tries--);

    return false;
}

bool RoboClone::ForwardM2(uint8_t value) {
    uint8_t tries = MAXRETRIES;

    do {
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(M2FORWARD);
        hserial->write(M2FORWARD);
        
        crc_update(value);
        hserial->write(value);

        hserial->write(crc >> 8);
        hserial->write(crc);

        if (read() == 0xff)
            return true;
    } while (tries--);

    return false;
}

bool RoboClone::BackwardM2(uint8_t value) {
    uint8_t tries = MAXRETRIES;

    do {
        crc = 0;

        crc_update(address);
        hserial->write(address);

        crc_update(M2BACKWARD);
        hserial->write(M2BACKWARD);
        
        crc_update(value);
        hserial->write(value);

        hserial->write(crc >> 8);
        hserial->write(crc);

        if (read() == 0xff)
            return true;
    } while (tries--);

    return false;
}
