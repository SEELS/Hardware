/*LCD pins
pin1 VSS = Ground
pin2 VDD = +5V
pin3 V0 = Ground
pin4 RS = 7
pin5 R/W = Ground
pin6 E = 6
pin11 D4 = 5
pin12 D5 = 4
pin13 D6 = 3
pin14 D7 = 2
pin15 A = +5V
pin16 k = Ground 
*/
#include<LiquidCrystal.h>
int RS=7;
int EN=6;
int D4=5;
int D5=4;
int D6=3;
int D7=2;


LiquidCrystal LCD(RS,EN,D4,D5,D6,D7);
//LiquidCrystal LCD(7,6,5,4,3,2);

void setup() {
 // set up the LCD's number of columns and rows:
 LCD.begin(16,2);
 LCD.print("Hello, SEELS!");

}

void loop() {
 // Turn off the display:
 LCD.noDisplay();
 delay(500);
 // Turn on the display:
 LCD.display();
 delay(500);
  
//LCD.setCursor(0,0);
//LCD.print("Sara");
//LCD.setCursor(0,1);
//LCD.print("Yasser ^_^");
}
