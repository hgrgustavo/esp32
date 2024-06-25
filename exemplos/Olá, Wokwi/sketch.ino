/* Olá Wokwi! */

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("Ola, Wokwi!");
}

void loop() {
    lcd.setCursor(7, 1);
    lcd.print(millis() / 1000);
}

