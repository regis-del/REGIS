#include <WiFi.h>
#include <HTTPClient.h>

#define red 19
#define green 21
#define blue 22
#define trig 18
#define echo 5

const char *ssid = "MANGOX_5G";
const char *password = "Rokiane@";

String serverName = "http://10.86.28.240/ultrasonic/insert.php";

float distance;
long duration;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);

  String motion;

  if (distance <= 10 && distance > 0) {
    digitalWrite(red, HIGH);
    motion = "Danger - Distance: " + String(distance) + "cm";
    Serial.println("RED LED ON");
  }
  else if (distance > 10 && distance <= 15) {
    digitalWrite(green, HIGH);
    motion = "Medium - Distance: " + String(distance) + "cm";
    Serial.println("GREEN LED ON");
  }
  else {
    digitalWrite(blue, HIGH);
    motion = "Safe - Distance: " + String(distance) + "cm";
    Serial.println("BLUE LED ON");
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String data = "motion=" + motion;

    int httpResponseCode = http.POST(data);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(3000);
}