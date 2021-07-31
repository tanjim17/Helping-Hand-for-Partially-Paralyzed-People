#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h>
#include<string.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

RH_ASK rf_driver;
SoftwareSerial mySerial(9, 10);

void setup()
{
  rf_driver.init();
  Serial.begin(1200);
  mySerial.begin(9600);

  // AT command to set mySerial to SMS mode
  mySerial.print("AT+CMGF=1\r");
  delay(100);

  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Helping Hand");
}

void send2Receiver(char command)
{
  char *msg = (char*)malloc(1 * sizeof(char));
  msg[0] = command;
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  delay(100);
}

void serialEvent()
{
  int command = Serial.read();
  Serial.print(F("I received: "));
  Serial.println(command);
  switch (command)
  {
    case 1:
      send2Receiver(1);
      printLCD("Turn on Fan");
      break;
    case 2:
      printLCD("Need Help");
      sendsms();
      break;
    case 3:
      printLCD("Call Medic");
      callMedic();
      break;
    case 4:
      printLCD("Calling Relative");
      callRelative();
      break;
    case 5:
      send2Receiver(5);
      printLCD("Turn on Light");
      break;
    case 6:
      send2Receiver(6);
      printLCD("Turn off Light");
      break;
    case 7:
      send2Receiver(7);
      printLCD("Turn off Fan");
      break;
    default:
      printLCD("Invalid Command");
      break;
  }
}

void printLCD(String message)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Command Found");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Helping Hand");
}

void sendsms()
{
  mySerial.println(F("AT\r"));
  delay(1000);
  mySerial.println(F("AT+CMGF=1\r"));
  delay(1000);
  mySerial.println(F("AT+CMGS=\"+8801766284110\"\r"));
  delay(1000);
  mySerial.println(F("Need help! Come asap!"));
  delay(1000);
  mySerial.println((char)26);
  delay(100);
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

void callRelative()
{
  mySerial.println("AT"); //Handshaking with SIM900
  delay(500);
  mySerial.println("ATD+ +8801912190720;");
  delay(500);
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  delay(500);
}

void loop()
{
  
}
