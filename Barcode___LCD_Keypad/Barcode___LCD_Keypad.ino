/*
Portable barcode scanner. Uses USB HID barcode scanner, Arduino Mega Board,
USB Host Shield , HD44780-compatible LCD display and Keypad
  The circuit for LCD:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

  The Circuit for Keypad:
 * First 4 pins are for Rows Connected with Arduino Pins {30,32,34,36}
 * Second  4 pins are for Cols Connected with Arduion pins 38,40,42,44}
*/

/*
#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <printhex.h>
#include <message.h>
#include <hexdump.h>
#include <parsetools.h>
#include <address.h>
*/
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <HIDBoot.h>
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <Keyboard.h>
#include <hid.h>
#include <hiduniversal.h>
#include <Keypad.h>

#define DISPLAY_WIDTH 16

//initialization Keupad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rowPins[ROWS] = {30,32,34,36}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {38,40,42,44}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad pad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

USB     Usb;
USBHub     Hub(&Usb);
HIDUniversal Hid(&Usb);
//HIDBoot <HID_PROTOCOL_KEYBOARD>    Keyboard(&Usb);

class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

protected:
    virtual void OnKeyDown  (uint8_t mod, uint8_t key);
    virtual void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
    uint8_t c = OemToAscii(mod, key);

    if (c)
        OnKeyPressed(c);
}

/* what to do when symbol arrives */
void KbdRptParser::OnKeyPressed(uint8_t key)
{
    static uint32_t next_time = 0;      //watchdog
    static uint8_t current_cursor = 0;  //tracks current cursor position

    if( millis() > next_time )
    {
        lcd.clear();
        current_cursor = 0;
        delay( 5 );  //LCD-specific
        lcd.setCursor( 0,0 );
    }//if( millis() > next_time ...

    next_time = millis() + 200;  //reset watchdog

    if( current_cursor++ == ( DISPLAY_WIDTH + 1 ))    //switch to second line if cursor outside the screen
    {
        lcd.setCursor( 0,1 );
    }

    Serial.print((char)key);
    lcd.print((char) key );
};

KbdRptParser Prs;

void setup()
{
    //Serial.begin( 115200 );
    Serial.begin(9600);
    Serial.println("Start");

    if (Usb.Init() == -1)
    {
        Serial.println("OSC did not start.");
    }

    delay( 200 );

    Hid.SetReportParser(0, (HIDReportParser*)&Prs);
    // set up the LCD's number of columns and rows:
    lcd.begin(DISPLAY_WIDTH, 2);
    lcd.clear();
    lcd.noAutoscroll();
    lcd.print("Ready ");
    delay( 200 );
}

void loop()
{
    Usb.Task();

    char key=pad.getKey();
    if(key=='1')
    {
        lcd.clear();
        lcd.print("1");
        Serial.println("Case 1");
    }
    else if(key=='2')
    {
        lcd.clear();
        lcd.print("2");
        Serial.println("Case 2");
    }
    else if(key=='3')
    {
        lcd.clear();
        lcd.print("3");
        Serial.println("Case 3 ");
    }
    else if(key=='4')
    {
        lcd.clear();
        lcd.print("4");
        Serial.println("Case 4 ");
    }
}
