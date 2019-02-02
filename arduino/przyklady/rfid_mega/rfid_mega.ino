/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO1 9
#define RESET_DIO1 8

#define SDA_DIO2 11
#define RESET_DIO2 10
/* Create an instance of the RFID library */
RFID RC1(SDA_DIO1, RESET_DIO1); 
RFID RC2(SDA_DIO2, RESET_DIO2);

void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC1.init();
  RC2.init();
}

void loop()
{
  /* Has a card been detected? */
  if (RC1.isCard())
  {
    /* If so then get its serial number */
    RC1.readCardSerial();
    Serial.println("Card detected:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC1.serNum[i],DEC);
    //Serial.print(RC1.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.println();
    Serial.println();
  }

  //rfid 2
  if (RC2.isCard())
  {
    /* If so then get its serial number */
    RC2.readCardSerial();
    Serial.println("Card detected:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC2.serNum[i],DEC);
    //Serial.print(RC2.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.println();
    Serial.println();
  }
  delay(1000);
}
