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

#include <stdlib.h>
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
//card number in for loop need to be correct when adding another one
//card keys 
//check if pin 13  12 is good for rfid reader  >> pin 0 opens door for few sec
//servo is attached in setup
//locked starting position
//writing from variable to blynk.virtualWrite(VARIABLE, int) doesnt work need to do manually -||-(V1,int)

#include <Keypad.h>
#include <Servo.h>
Servo ServoMotor;

//rfid
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO0 3
#define RESET_DIO0 2

#define SDA_DIO1 5    //9 this is old was working
#define RESET_DIO1 4  //8

#define SDA_DIO2 7
#define RESET_DIO2 6

#define SDA_DIO3 9
#define RESET_DIO3 8

#define SDA_DIO4 11
#define RESET_DIO4 10
/* Create an instance of the RFID library */
RFID RC0(SDA_DIO0, RESET_DIO0);
RFID RC1(SDA_DIO1, RESET_DIO1); 
RFID RC2(SDA_DIO2, RESET_DIO2);
RFID RC3(SDA_DIO3, RESET_DIO3);
RFID RC4(SDA_DIO4, RESET_DIO4);


//String pinStr;
//int pinNumber;
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



////testing 

RFID rfids[] = {RC0,RC1,RC2,RC3,RC4};
String doorKeys[] = {"SPECIAL","ASD","DKFNA","DKFNA","DKFNA"}; //when placing rfid runs scan through those
String rfidKeys[] = {"ASDDSA","DKFNA","NFBASBD","BNSDABA"}; //4 klucze po kolei 
//compares position of rfid to position key // if every key can open door , add these to doorKeys

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  SPI.begin();
  
  RC0.init();
  RC1.init();
  RC2.init();
  RC3.init();
  RC4.init();
  
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



//testing

      Blynk.virtualWrite(V1 , 1000);
      Blynk.virtualWrite(V2 , 1000);
      Blynk.virtualWrite(V3 , 1000);
      Blynk.virtualWrite(V4 , 1000);
  
 

  Serial.println();
  Serial.println("Approximate your card to the reader...");
}



void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  Serial.println("loop");
  //Blynk.virtualWrite(V3, 255); this is tested , works
  
  //rfid

  if (RC0.isCard()){
    /* If so then get its serial number */
    RC0.readCardSerial();
    String content = "";
    Serial.println("Card detected:");
    for(int i=0;i<5;i++){
    Serial.print(RC0.serNum[i],DEC);
    //content.concat(String(RC1.serNum[i],DEC));
    //Serial.print(RC1.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    
    content.toUpperCase();
    for(String key : doorKeys){
      if(content == key){
        LockedPosition(0);
        return;
      }else{
        //LockedPosition(1);  
      }
    }
  }
  
  delay(2000);  //check for door key every sec , check for all keys every 2 sec

  

  for(int r=1; r<=4;r++){
    
    String pinStr = "V";
    pinStr.concat(r);
    //int pinNumber = pinStr.toInt();

    
    if(rfids[r].isCard()){
        rfids[r].readCardSerial();
        String content = "";
        Serial.println("Card detected:");
        
        for(int i=0;i<5;i++){
        Serial.print(RC1.serNum[i],DEC);
        content.concat(String(RC1.serNum[i],DEC));
        //Serial.print(RC1.serNum[i],HEX); //to print card detail in Hexa Decimal format
        }
        content.toUpperCase();

        
        
        if(validCard(content, r)){
          LockedPosition(0);
          //Blynk.virtualWrite(pinNumber, 255); //do this
        }else{
          //LockedPosition(1);  
        }
    }else{
      Serial.println("else"+ pinStr);
      delay(1000);
      lightVLed(pinStr,0);
    }
  }

  

  //Blynk.virtualWrite(V1, test);
  //delay(2000);
}

void lightVLed(String value, int turned){

  if(value == "V1"){
    Blynk.virtualWrite(V1, turned);
  }else if(value == "V2"){
    Blynk.virtualWrite(V2, turned);
  }else if(value == "V3"){
    Blynk.virtualWrite(V3, turned);
  }else if(value == "V4"){
    Blynk.virtualWrite(V4, turned);
  }

}

bool validCard(String key, int rfid){
  if(key == rfidKeys[rfid-1]){
    return true;
  }else{
    return false;
  }
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
