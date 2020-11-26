#include <Arduino.h>
#include "HAL.h"

HAL::HAL()
{
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.clear(true);
}


void HAL::setBrightness(uint8_t brightness)
{
    FastLED.setBrightness(brightness);
}

uint8_t HAL::getBrightness()
{
    return FastLED.getBrightness();
}

void HAL::update(byte (&buffer)[7][6])
{
    int pos = 0;
    for (size_t h = 0; h < 6; h++)
    {
        for (size_t w = 0; w < 7; w++)
        {
        if (buffer[w][h] == COLOR_PLAYER_1)
        {
            leds[pos] = CRGB::Red;
        }
        else if (buffer[w][h] == COLOR_PLAYER_2)
        {
            leds[pos] = CRGB::Yellow;
        }
        else
        {
            leds[pos] = CRGB::Black;
        }
        pos++;
    }
  }
  FastLED.show();
}


void HAL::clear()
{
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}


void HAL::testLoad(uint32_t color, uint16_t timedelay)
{
    for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
    FastLED.show();
    delay(timedelay);
  }
}


void HAL::epilepticTest(int times)
{
  for (size_t j = 0; j < times; j++)
  {
    for (size_t i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::GreenYellow;
    }
    FastLED.show();
    delay(30);

    for (size_t i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(30);
  }
}



void HAL::testVertical()
{
  byte output[7][6];
  for (size_t w = 0; w < 7; w++)
  {
    for (size_t h = 0; h < 6; h++)
    {
      if (h % 2 == 0)
      {
        output[w][h] = COLOR_PLAYER_1;
      }
      else
      {
        output[w][h] = COLOR_PLAYER_2;
      }
    }
  }
  update(output);
}



void HAL::testHorizontal()
{
  byte output[7][6];
  for (size_t w = 0; w < 7; w++)
  {
    for (size_t h = 0; h < 6; h++)
    {
      if (w % 2 == 0)
      {
        output[w][h] = COLOR_PLAYER_1;
      }
      else
      {
        output[w][h] = COLOR_PLAYER_2;
      }
    }
  }
  update(output);
}