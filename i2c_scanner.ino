/*
  This sketch scans for the i2c slave address of a device. This uses the LCD library by David A. Mellis which got modified by Limor Fried and Tim Igoe.

  Changed LCD connections to work with barebones MSP430(M430G2553)
  =================================
  LCD pin              Connect to
  ---------------------------------
  01 - GND             GND, pot
  02 - VCC             +5V, pot
  03 - Contrast        Pot wiper
  04 - RS              Pin6 (P1.4)
  05 - R/W             GND
  06 - EN              Pin7 (P1.5)
  07 - DB0             GND
  08 - DB1             GND
  09 - DB2             GND
  10 - DB3             GND
  11 - DB4             Pin8 (P2.0)
  12 - DB5             Pin11 (P2.3)
  13 - DB6             Pin12 (P2.4)
  14 - DB7             Pin13 (P2.5)
  15 - BL+             +5V
  16 - BL-             GND
  =================================
  
  Augmented by: HyperChiicken
*/

#include <LiquidCrystal.h>
#include <Wire.h>

uint8_t error, address;
const int buttonPin = PUSH2;     // the number of the pushbutton pin
const int ledPin =  RED_LED;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

/* Initialize the library with the numbers of the interface pins */
LiquidCrystal lcd(P1_4, P1_5, P2_0, P2_3, P2_4, P2_5);

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);          // initialize the LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP); // initialize the pushbutton pin as an input
  lcd.begin(20, 4);                 // set up the LCD's number of columns and rows
  Wire.begin(0);                    // start i2c communications
  
  /* Print an opening message to the LCD */
  lcd.print("     I2C_Scanner");
  lcd.setCursor(0, 2);
  lcd.print("Press button to SCAN");
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    startScan();                    // start scanning when the button is pressed
  }
}

/* Scans for the i2c slave address by iterating from 1 to 126 */
void startScan() {
  digitalWrite(ledPin, LOW); 
  for (address = 1; address < 127; address++ )
  {
    lcd.setCursor(0, 1);
    lcd.print("Scanning...");
    lcd.print(address);

    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    /* Display the slave address in HEX when found */
    if (error == 0) {
      lcd.setCursor(0, 2);
      lcd.print("Found Address:      ");
      lcd.setCursor(0, 3);
      lcd.print("0x");
      
      if (address < 15) lcd.print('0');
      lcd.print(address, HEX);
    }
  }
}
