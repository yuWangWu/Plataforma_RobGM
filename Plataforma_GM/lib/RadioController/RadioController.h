#include "Arduino.h"

#define CH1PIN  25
#define CH2PIN  26
#define CH3PIN  27
#define CH4PIN  32
#define CH5PIN  33
#define CH6PIN  34

class RadioController {
private: 
    // Internal variables
    unsigned long ch1Initial{}, ch1End{}, ch2End{}, ch3End{}, ch4End{}, ch5End{}, ch6End{};
    unsigned long ch1Value{}, ch2Value{}, ch3Value{};
    bool ch4Value{}, ch5Value{}, ch6Value{};

    // Interrupt methods
    void IRAM_ATTR ch1INTRR();
    void IRAM_ATTR ch2INTRR();
    void IRAM_ATTR ch3INTRR();
    void IRAM_ATTR ch4INTRR();
    void IRAM_ATTR ch5INTRR();
    void IRAM_ATTR ch6INTRR();
public:
    void begin();

    // Getters
    int getCH1Value() { return ch1Value; }
    int getCH2Value() { return ch2Value; }
    int getCH3Value() { return ch3Value; }
    bool getCH4Value() { return ch4Value; }
    bool getCH5Value() { return ch5Value; }
    bool getCH6Value() { return ch6Value; }
};



