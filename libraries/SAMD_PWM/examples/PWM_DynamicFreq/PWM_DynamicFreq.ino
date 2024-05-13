/****************************************************************************************************************************
  PWM_DynamicFreq.ino

  For SAMD21/SAMD51 boards using hardware-based PWM
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/SAMD_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_       4

#include "SAMD_PWM.h"

// Not OK for Nano_33_IoT (0, 1, 7, 8, 13, 14, 15 )
// OK for Nano_33_IoT (2, 3, 4, 5, 6, 9, 10, 11, 12, 16, 17)
// TCC OK => pin 4, 5, 6, 8, 9, 10, 11, 16/A2, 17/A3
// TC OK  => pin 12
// For ITSYBITSY_M4
// 16-bit Higher accuracy, Lower Frequency, PWM Pin OK: TCCx: 0-2, 4, 5, 7, 9-13
//  8-bit Lower  accuracy, Hi Frequency,    PWM Pin OK: TCx: 18-20, 24-25

#define pinToUse       11

//creates pwm instance
SAMD_PWM* PWM_Instance;

float frequency;

char dashLine[] = "=====================================================================================";

void printPWMInfo(SAMD_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DC = ");
  Serial.print(PWM_Instance->getActualDutyCycle());
  Serial.print(", PWMPeriod = ");
  Serial.print(PWM_Instance->getPWMPeriod());
  Serial.print(", PWM Freq (Hz) = ");
  Serial.println(PWM_Instance->getActualFreq(), 4);
  Serial.println(dashLine);
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting PWM_DynamicFreq on "));
  Serial.println(BOARD_NAME);
  Serial.println(SAMD_PWM_VERSION);

  frequency = 10000.0f;
  PWM_Instance = new SAMD_PWM(pinToUse, frequency, 50.0f);

  if (PWM_Instance)
  {
    PWM_Instance->setPWM();
  }

  Serial.println(dashLine);
}

void loop()
{
  delay(5000);

  // Not OK yet, TODO
  frequency = 20000.0f;

  Serial.print(F("Change PWM Freq to "));
  Serial.println(frequency);
  PWM_Instance->setPWM(pinToUse, frequency, 50.0f);
  printPWMInfo(PWM_Instance);

  delay(5000);

  frequency = 10000.0f;

  Serial.print(F("Change PWM Freq to "));
  Serial.println(frequency);
  PWM_Instance->setPWM(pinToUse, frequency, 50.0f);
  printPWMInfo(PWM_Instance);
}
