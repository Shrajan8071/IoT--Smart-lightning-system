#include <WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <HTTPClient.h>
const char *ssid = "TABLET";       // Your WiFi SSID
const char *password = "qwerty1234";   // Your WiFi password

const char *thingSpeakApiKey = "W4VM9K5CRC056VU4";   // Your ThingSpeak API Key
const unsigned long postingInterval =1;  // Interval at which to send data (in milliseconds)

 // Define the pin number
int pir_sensor = 0;
unsigned long lastConnectionTime = 0; 
WiFiClient client;
const int pirPin = 12;    // PIR sensor pin
const int ledPin = 26;    // LED pin
const int delayTime = 1000; // Delay time in milliseconds (10 seconds)

bool personDetected = false; // Variable to track if a person is detected
HTTPClient http;
void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

  pinMode(12, INPUT);
  pinMode(26, OUTPUT);

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
 int data = readData(); 

 if (data == 1) {
    ThingSpeak.writeField(2468931, 1, digitalRead(pirPin), thingSpeakApiKey);
    digitalWrite(ledPin, LOW); // Turn on the LED
    Serial.println("Person detected, LED ON");
  }
  else {
    delay(100);
      // data = readData(); 
      // if (data == 0) {
        digitalWrite(ledPin, HIGH);
        Serial.println("No person detected, LED OFF");
      // }
    }
  
  ThingSpeak.writeField(2468931, 1, digitalRead(pirPin), thingSpeakApiKey);

}

int readData(){
  int data = ThingSpeak.readIntField(2468931, 1, "MOYL68B9CQYORO46");
  return data;
}
