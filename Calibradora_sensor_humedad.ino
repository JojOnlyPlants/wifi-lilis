#define AOUT_PIN 36 

void setup() {
  Serial.begin(115200);
  pinMode(36, INPUT);
}
void loop() {
  int value = analogRead(AOUT_PIN); // read the analog value from sensor
if (value<1000); {
  Serial.println(value);
    Serial.println("Bien Humedo");//1300 a 2000 "Humedo"
   }
delay(1000);
}
