#pragma once

#include <NoiascaLiquidCrystal.h>                // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
#include <utility/NoiascaCustomCharacters.h>     // file with several predefined custom characters

const byte cols = 16;                            // columns/characters per row
const byte rows = 2;                             // how many rows
const byte addr = 0x27;

#include <Wire.h>
#include <NoiascaHW/lcd_PCF8574.h>               // I2C
LiquidCrystal_PCF8574 lcd(addr, cols, rows, convert_custom);         // create lcd object I2C

void customCharacterMapping_ge() {
  //  This UTF8 code will become  -->   that custom character
  utf8_to_customChar[4] = 0xC384;    lcd.createChar_P(4, latin_capital_a_diareses);      // Ä
  utf8_to_customChar[5] = 0xc396;    lcd.createChar_P(5, latin_capital_o_diareses);      // Ö   
  utf8_to_customChar[6] = 0xc39c;    lcd.createChar_P(6, latin_capital_u_diareses);      // Ü   
  utf8_to_customChar[7] = 0xc39F;    lcd.createChar_P(7, latin_small_sharp_s);           // ß    
}

void InitLCDGerman() {
  Wire.begin();                        // start the I2C bus - activate if needed for the display
  lcd.begin();                         // initialize the lcd
  lcd.backlight();
  customCharacterMapping_ge();
}

