#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
String texto;
String tmp;

void setup() {
  lcd_1.begin(16, 2);
  lcd_1.setCursor(1, 1);
  lcd_1.print("ICO FES ARAGON");
  texto = "JORGE LUIS CANDELARIO ALAVEZ ";
}

void loop() {
	for(int i = 0; i < (texto.length() - 16); i++){
      	lcd_1.setCursor(0, 1);
  		lcd_1.print("ICO FES ARAGON");
        lcd_1.setCursor(0, 0);
  		lcd_1.print(texto.substring(i, (16 + i)));
      	delay(500);
    }
  tmp = texto;
  texto = tmp.substring((tmp.length() - 16), tmp.length()) + tmp.substring(0, (tmp.length() - 16));
}
