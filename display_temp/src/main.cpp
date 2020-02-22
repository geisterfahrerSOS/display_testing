#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Kompass.h>

#define CTRL5 0x24
#define ADDRESS1 0x1D
#define TEMP_OUT_L 0x05
#define TEMP_OUT_H 0x06

uint8_t comp8 (uint8_t wert);


LiquidCrystal_I2C lcd(0x27, 16, 2);
Winkel kmp = Winkel();
void setup()
{
	Serial.begin(9600);
	lcd.begin();
	pinMode(10, INPUT_PULLUP);
	kmp.startup();
}
float temp;
int wert;
float ges;
void loop()
{
	kmp.chipWrite(CTRL5, 0b10011000);

	lcd.clear();

	lcd.home();
	lcd.print(kmp.chipRead(TEMP_OUT_L), BIN);
	lcd.setCursor(0, 1);
	lcd.print(comp8(kmp.chipRead(TEMP_OUT_L)), BIN);

	ges=0;
	if (kmp.chipRead(TEMP_OUT_L) & 0b10000000)
	{
		ges -= 128;
	}
	else
	{
		ges += 128;
	}
	for (int i = 0; i <= 6; i++)
	{
		if (kmp.chipRead(TEMP_OUT_L) & (int)pow(2, i))
		{
			ges += (int)pow(2, i);
		}
	}
	lcd.setCursor(9, 1);
	lcd.print(comp8(kmp.chipRead(TEMP_OUT_L)), DEC);
	delay(300);

}

uint8_t comp8 (uint8_t wert){
	wert = ~wert;
	wert += 0b00000001;
	return wert;
}

	//Bar graph
	// 		if (kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L) > 32768)
	// 	{
	// 		temp = 65536 - kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L);
	// 	}
	// 	else
	// 	{
	// 		temp = kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L);
	// 	}
	// wert = map(temp, 0, 30, 0, 16);
	// for(int i = 0; i<=wert; i++)
	// {
	// 	lcd.setCursor(i,0);
	// 	lcd.print("X");
	// 	Serial.println(temp);
	// 	Serial.println(wert);
	// }
	// lcd.setCursor(0,1);
	// lcd.print("0 C");
	// lcd.setCursor(13,1);
	// lcd.print("30 C");
	// delay(200);

	// lcd.setCursor(0,0);
	// lcd.print("binary");
	// lcd.setCursor(10,0);
	// lcd.print(0b00101001,BIN);
	// lcd.setCursor(0,1);
	// lcd.print("2 compl");
	// lcd.setCursor(8,1);
	// lcd.print(comp8(0b00101001),BIN);
	// if (digitalRead(10))
	// {
	// 	lcd.setCursor(0,1);
	// 	if (kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L) > 32768)
	// 	{
	// 		lcd.print(65536 - kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L), DEC);
	// 	}
	// 	else
	// 	{
	// 		lcd.print(kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L), DEC);
	// 	}
	// }
	// else
	// {
	// 	lcd.setCursor(0,0);
	// 	if (kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L) > 32768)
	// 	{
	// 		lcd.print(65536 - kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L), BIN);
	// 	}
	// 	else
	// 	{
	// 		lcd.print(kmp.read12bit(TEMP_OUT_H, TEMP_OUT_L), BIN);
	// 	}
	// }