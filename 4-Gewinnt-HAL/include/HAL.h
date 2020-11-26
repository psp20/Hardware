#pragma once
#include "FastLED.h"
#include "HardwareDefines.h"

class HAL
{
private:
    CRGB leds[NUM_LEDS];
public:
    HAL();
    ~HAL();
    void setBrightness(uint8_t brightness);
    uint8_t getBrightness();
    void update(byte (&buffer)[7][6]);
    void clear();

    void testLoad(uint32_t color, uint16_t timedelay = 500);
    void epilepticTest(int times);
    void testVertical();
    void testHorizontal();
};

