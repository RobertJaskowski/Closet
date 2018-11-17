
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "szafka-e1401.firebaseio.com"
#define FIREBASE_AUTH "tTUZTPknZjDu1s71OzwKTwWpWRiLq9ehQGYhiPdo"
#define WIFI_SSID "FunBox2-E53D"
#define WIFI_PASSWORD "jaskowski"

void setup() {
  Serial.begin(9600);                        
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {           //wait till connected to WiFi
    delay(100);  
    digitalWrite(WIFI_LED,LOW);                     //Blink the light till connected to WiFi
    delay(100);
    digitalWrite(WIFI_LED,HIGH);
    Serial.print("."); }
    
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(WIFI_LED,HIGH);  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);             //connect to Database
  delay(1000);
}

void loop() {
  String firebaseResult = firebaseGet();
  delay(100);
  if (firebaseResult=="ON"){
      //code to happen if the status is ON  
  }else{
      //code to happen if the status is OFF
    }
}
