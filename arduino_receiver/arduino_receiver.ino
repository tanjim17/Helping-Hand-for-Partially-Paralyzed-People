#include<math.h>
#include <RH_ASK.h>
#include <SPI.h>

#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5

#define room_length 28

RH_ASK rf_driver;

volatile int d1;
volatile int d2;

void setup()
{
  rf_driver.init();
  Serial.begin(1200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}


long sonar(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;
  return distance;
}

void findRoom()
{
  d1 = 0;
  d2 = 0;
  for(int i=0;i<3;i++)
  {
    d1 += sonar(trigPin1, echoPin1);
    d2 += sonar(trigPin2, echoPin2);
    delay(100);
  }
  d1 = (int)(d1/3.0);
  d2 = (int)(d2/3.0);
}

char calculateAngle(char select)
{
  int distance;
  if (select == 0x01) // room1
  {
    distance = d1;
  }
  else // room2
  {
    distance = d2;
  }

  if (distance<8) // 60 degree
  {
    return 0xC3;
  }
  else if (distance <15) // 60 degree
  {
    return 0xC4;
  }
  else if (distance<20) // 75 degree
  {
    return 0xC6;
  }
  else // 90 degree
  {
    return 0xC5;
  }
  
}

void loop()
{
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("Message Received: ");
    Serial.println(buf[0]);

    findRoom();
    Serial.print(d1);
    Serial.print("-");
    Serial.println(d2);

    int room1 = false;
    int room2 = false;
    if (d1 < room_length && d1 < d2)
    {
      room1 = true;
    }
    else if (d2 < room_length)
    {
      room2 = true;
    }

    // RRL - Turn on fan - 1
    // LRL - Turn on light - 5
    // LLL - Turn Off Fan - 7
    // LLR - Turn Off Light - 6
    switch (buf[0])
    {
      case 1:
        if (room1)
        {
          Serial.write(1);
          delay(500);
          Serial.write(calculateAngle(0x01));
        }
        else if (room2)
        {
          Serial.write(5);
          delay(500);
          Serial.write(calculateAngle(0x02));
        }
        break;
      case 5:
        if (room1)
        {
          Serial.write(2);
        }
        else if (room2)
        {
          Serial.write(6);
        }
        break;
      case 7:
        if (room1)
        {
          Serial.write(3);
          delay(500);
          Serial.write(0xC2);
        }
        else if (room2)
        {
          Serial.write(7);
          delay(500);
          Serial.write(0xC2);
        }
        break;
      case 6:
        if (room1)
        {
          Serial.write(4);
        }
        else if (room2)
        {
          Serial.write(8);
        }
        break;
    }
  }
}
