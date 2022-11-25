/*
  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  Once it connects successfully to a Wifi network and a MQTT broker, it subscribe to a topic and send a message to it.
  It will also send a message delayed 5 seconds later.
*/
#include "EspMQTTClient.h"
#define AOUT_PIN 36 //Definimos entrada de humedad de tierra
#include <DHT.h>
#include "DHT.h"
#include <DHT_U.h>
int Led1 = 17;  
int Led2 =16;
int Led3 =15;
int Led4 =14;
int Led5 =13;
const int buttonPin = 4;
int buttonState = 0;        
int count_value =0;
int prestate =0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;
EspMQTTClient client(
  "SSID",
  "CONTRASEÑA",
  "test.mosquitto.org",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "Caporal",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);
const int h=0;
DHT dht(32, DHT11);
void setup()
{
 startMillis = millis();
 dht.begin();
 pinMode(36, INPUT);
 pinMode(Led1, OUTPUT); //Declaramos LEDs como salidas
pinMode(Led2, OUTPUT);
pinMode(Led3, OUTPUT);
pinMode(Led4, OUTPUT);
pinMode(Led5, OUTPUT);
pinMode(buttonPin, INPUT);
int s = analogRead(AOUT_PIN);
  Serial.begin(115200);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("mytopic/test", [](const String & payload) {
    Serial.println(payload);
  });

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  client.subscribe("caporal", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });

  // Publish a message to "mytopic/test"
  client.publish("mytopic/capo", "ZOLA"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
  client.executeDelayed(5 * 1000, []() {
    client.publish("caporal", "PRUEBA DE AMOR");
  });
}

void loop()
{
  float e=0;
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    count_value++;
    delay(100);
  }
  if   (1 < count_value){
  digitalWrite(Led1, HIGH);
  e=1; }
  if    (2 < count_value){
  digitalWrite(Led2, HIGH);
  e=2;}
  if    (3 < count_value){
  digitalWrite(Led3, HIGH);
  e=3;}
  if    (4 < count_value){
  digitalWrite(Led4, HIGH);
  e=4;}
  if    (5 < count_value){
  digitalWrite(Led5, HIGH);
  e=5;}
  if   (6 < count_value){
 digitalWrite(Led1, LOW);
    digitalWrite(Led2, LOW);
    digitalWrite(Led3, LOW);
    digitalWrite(Led4, LOW);
    digitalWrite(Led5, LOW);  
e=0;}
  client.loop();
int s = analogRead(AOUT_PIN);
String z;
z=String(s);
float h = dht.readHumidity();
float t = dht.readTemperature();
String c;
c=String(t);
String u;
u=String(h);
String r;
r=String (e);
//currentMillis = millis();  
  //if (currentMillis - startMillis >= period){ 
client.publish("caporal/s",z);
client.publish("caporal/t",c);
client.publish("caporal/h",u);
client.publish("caporal/r",r);
  delay(2000);
  //startMillis = currentMillis;}
}
