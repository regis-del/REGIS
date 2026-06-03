#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MANGOX_5G";
const char* password = "Rokiane@";

String serverName = "http:// 10.85.250.239/ultrasonic/insert.php?distance=";

#define trigPin 1
#define echoPin 2

#define greenLED 5
#define yellowLED 6
#define redLED 7

#define buzzer 8

WiFiClient client;

void setup() {

  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }

  Serial.println("");
  Serial.println("WiFi Connected");

}

void loop() {

  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED and Buzzer Control

  if(distance > 20) {

    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    digitalWrite(buzzer, LOW);

  }
  else if(distance > 10 && distance <= 20) {

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    digitalWrite(buzzer, LOW);

  }
  else {

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    digitalWrite(buzzer, HIGH);

  }

  // Send data to server

  if(WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String serverPath = serverName + String(distance);

    http.begin(client, serverPath.c_str());

    int httpResponseCode = http.GET();

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    http.end();

  }

  delay(3000);

}