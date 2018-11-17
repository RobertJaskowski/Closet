
//one pin keypad
//https://www.youtube.com/watch?v=W8ZSeLD90KA&t=5s  
//things to check
//firebase included zip



#include <Keypad.h>
#include <Servo.h>

//rfid
#include <SPI.h>
#include <MFRC522.h>

//firebase
//#include <FirebaseArduino.h>         




#define SS_PIN 24
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN); 

Servo ServoMotor;

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


void setup(){
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
  
   //ServoMotor.attach(11);
  //LockedPosition(true);
  
    //pinMode(13, OUTPUT);
    
   // pinMode(12, OUTPUT);
   Serial.println("Approximate your card to the reader...");
}

void loop(){
  //Serial.println("Hello world kappa.");
//  digitalWrite(13, HIGH);
  
//  digitalWrite(13, LOW);
  
  
  
  
  char key = customKeypad.getKey();
  if (key){
    Serial.println(key);
  
      if (key == '*' || key == '#')
    {
      position = 0;
      LockedPosition(true);
    }
    if (key == password[position])
    {
      position ++;
      tone(13, 4000, 100);
    }
    if (position == 3)
    {
      LockedPosition(false);
      
    }
  }
    

  //rfid

   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "2A 4F B0 10") //change here the UID of the card/cards that you want to give access
  {
    
//    digitalWrite(diodaCzerwona,HIGH);
//    delay(1000);
//    digitalWrite(diodaZolta,HIGH);
//    delay(1000);
//    digitalWrite(diodaZielona,HIGH);

    
    
    
    Serial.println("Authorized access");
    Serial.println();
    
//       for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//      // in steps of 1 degree
//      myservo.write(pos);              // tell servo to go to position in variable 'pos'
//      delay(15);                       // waits 15ms for the servo to reach the position
//    }
//    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//      myservo.write(pos);              // tell servo to go to position in variable 'pos'
//      delay(15);                       // waits 15ms for the servo to reach the position
//    }

    
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}


void LockedPosition(int locked){
  if (locked)
  {
      ServoMotor.write(11);
  }
  else
  {
    
    digitalWrite(12, HIGH);
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(12, LOW);
    delay(1000);
    ServoMotor.write(90);
  }
}
