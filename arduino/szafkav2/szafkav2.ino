/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App project setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e3edddbe8c3d4f65b8e078942aa5f0cc";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "ENERGETYK_MOCNI";
//char pass[] = "qwerty2014";

char ssid[] = "FunBox2-E53D";
char pass[] = "jaskowski";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

BlynkTimer timer;


////my code
//before starting need to define what pins for :
//ss_pin
//rst_pin
//

#include <Keypad.h>
#include <Servo.h>
Servo ServoMotor;

//rfid
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

String KF = "Free";
String KT = "Taken";

char* password = "123"; 
int position = 0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

int pos = 0;

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  SPI.begin();
  
  RC1.init();
  RC2.init();

  //ServoMotor.attach(11);
  //LockedPosition(true);

  
  

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

  //Blynk.virtualWrite(V1, "openn");
  //Blynk.virtualWrite(V2, "closedd");
  //Blynk.virtualWrite(V3, 5000);
  //Blynk.virtualWrite(V4, 60);


  
 

  Serial.println();
  Serial.println("Approximate your card to the reader...");
}

RFID[] 

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  //rfid

  

  if (RC1.isCard()){
    /* If so then get its serial number */
    RC1.readCardSerial();
    String content = "";
    Serial.println("Card detected:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC1.serNum[i],DEC);
    //content.concat(String(RC1.serNum[i],DEC));
    //Serial.print(RC1.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }

    content.toUpperCase();
    if(content.substring(1) == "ASD ASD"){
      LockedPosition(0);
      writeToBlynk(V1,KT);
    }else{
      //LockedPosition(1);  
    }
  }

  //rfid 2
  //Blynk.virtualWrite(V1, test);
  //delay(2000);
}

void writeToBlynk(int pin,String value){
  Blynk.virtualWrite(pin, value);
}


void LockedPosition(int locked){
  if (locked)
  {
    //close
      ServoMotor.write(11);

      
  }else{
    //open
    
//    digitalWrite(12, HIGH);
//    delay(1000); 
//    digitalWrite(12, LOW);
//    delay(1000);
   // ServoMotor.write(90);
  }
}
