#include <DFRobot_MAX30102.h>

DFRobot_MAX30102 particleSensor;

void setup()
{
  Serial.begin(1200);
  while (!particleSensor.begin())
  {
    Serial.println("MAX30102 was not found");
    delay(1000);
  }
  particleSensor.sensorConfiguration(/*ledBrightness=*/50, /*sampleAverage=*/SAMPLEAVG_4, \
                        /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_100, \
                        /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_16384);
}

int32_t SPO2; //SPO2
int8_t SPO2Valid; //Flag to display if SPO2 calculation is valid
int32_t heartRate; //Heart-rate
int8_t heartRateValid; //Flag to display if heart-rate calculation is valid
int highHeartRateCount; //for how many consecutive interations heart rate stayed high

void loop()
{
  Serial.println(F("Wait about four seconds"));
  particleSensor.heartrateAndOxygenSaturation(/**SPO2=*/&SPO2, /**SPO2Valid=*/&SPO2Valid, /**heartRate=*/&heartRate, /**heartRateValid=*/&heartRateValid);

  Serial.print(F("heartRate = "));
  Serial.print(heartRate, DEC);
  if(heartRate > 50) //heart rate above 50 is considered to be high (for demonstration purpose)
  {
    highHeartRateCount ++;
    if(highHeartRateCount == 3) //if heart rate stays high for three iterations consecutively, signal will be sent
    {
      Serial.write(1);
      highHeartRateCount = 0;
    }
  }
  else
  {
    highHeartRateCount = 0;  
  }
  Serial.print(F(", isValid = "));
  Serial.println(heartRateValid, DEC);
//  Serial.print(F("; SPO2="));
//  Serial.print(SPO2, DEC);
//  Serial.print(F(", SPO2Valid="));
//  Serial.println(SPO2Valid, DEC);
}
