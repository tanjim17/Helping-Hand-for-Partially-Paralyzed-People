#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup()
{
  Serial.begin(1200);
  mySerial.begin(9600);

  // AT command to set mySerial to SMS mode
  mySerial.print("AT+CMGF=1\r");
  delay(100);
}

void serialEvent()
{
  int command = Serial.read();
  Serial.print(F("I received: "));
  Serial.println(command);
  switch (command) {
    case 1:
      callMedic();
      break;
  }
}

void callMedic()
{
  mySerial.println("AT"); //Handshaking with SIM900
  delay(500);
  mySerial.println("ATD+ +8801766284110;");
  delay(500);
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  delay(500);
}

void loop()
{

}
