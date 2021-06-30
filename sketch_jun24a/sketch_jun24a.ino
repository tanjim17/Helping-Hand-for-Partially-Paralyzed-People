#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  // Robojax code for LCD with I2C
  // initialize the LCD, 
  lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();
  // Robojax code for LCD with I2C


}

void loop()
{
  
  //start of loop Robojax code for LCD with I2C
  lcd.clear();
  lcd.print("Robojax");
  lcd.setCursor (0,1); // go to start of 2nd line
 lcd.print("Hello World!");
  //lcd.print(millis() / 1000);
  delay(500);
 //end of loopcode Robojax code for LCD with I2C
}
