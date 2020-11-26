#include <Arduino.h>
#include "HAL.h"

HAL *pa;
byte buffer[7][6];


void setup()
{
  Serial.begin(9600);
  Serial.println("Beginn");
  pa = new HAL();
  for (uint8_t w = 0; w < 7; w++)
  {
    for (uint8_t h = 0; h < 6; h++)
    {
      buffer[w][h] = 0;
    } 
  }
}



void loop()
{
  char dataIn[20];

  Serial.println("Loop beginn");
  pa->setBrightness(35);
  pa->testLoad(CRGB::Blue, 100);
  delay(500);
  pa->clear();
  delay(500);
  pa->testLoad(CRGB::Cornsilk, 50);
  delay(1000);
  pa->testVertical();
  delay(1000);
  pa->testHorizontal();
  delay(1000);
  pa->epilepticTest(50);
  delay(5000);

  while (true)
  {
    int x, y;

    Serial.println("\nWaiting for Input...");
    Serial.print("Spalte (1-7):\t");
    while (Serial.available())
    {
      while (!Serial.readBytes(dataIn, 1))
      {
        sleep(1);
      }
      Serial.println(dataIn[0]);
      x = ((int) (dataIn[0] - '0'))-1;
      dataIn[0] = '0';
      Serial.println(dataIn[0]);



      Serial.print("Zeile (1-6):\t");
      while (!Serial.readBytes(dataIn, 1))
      {
        sleep(1);
      }
      Serial.println(dataIn[0]);
      y = ((int) (dataIn[0] - '0'))-1;
      dataIn[0] = '0';



      Serial.print("Player (1, 2):\t");
      while (!Serial.readBytes(dataIn, 1))
      {
        sleep(1);
      }
      Serial.println(dataIn[0]);
      if (dataIn[0] == '1')
      {
        buffer[x][y] = COLOR_PLAYER_1;
        pa->update(buffer);
      }
      else
      {
        buffer[x][y] = COLOR_PLAYER_2;
        pa->update(buffer);
      }
    }
    delay(2000);
  }
}