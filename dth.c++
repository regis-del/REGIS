
 #include <WiFi.h>
 #include <HTTPClient.h>
 #include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// WiFi Name and Password
const char* ssid = "MANGOX_5G";
const char* password = "Rokiane@";

// Server URL
String serverName = "http://10.27.176.185/iot_dht/insert.php";

// LED Pins
#define greenLED 5
#define yellowLED 6
#define redLED 7

// Buzzer Pin
#define buzzer 8

void setup() {

  Serial.begin(115200);

  dht.begin();

  // LED Setup
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Buzzer Setup
  pinMode(buzzer, OUTPUT);

  // Turn OFF all LEDs and buzzer initially
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Read Temperature and Humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if reading failed
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("Failed to read from DHT sensor");

    // RED LED and buzzer ON when sensor fails
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);

    delay(2000);
    return;
  }

  // Print values on Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // LED and Buzzer Conditions
  if (temperature < 25) {

    // GREEN LED ON
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

  } else if (temperature >= 25 && temperature < 35) {

    // YELLOW LED ON
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

  } else {

    // RED LED and buzzer ON
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  // Send data to server
  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    HTTPClient http;

    String url = serverName +
                 "?temperature=" + String(temperature) +
                 "&humidity=" + String(humidity);

    Serial.println(url);

    http.begin(client, url);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);

      Serial.println("Server Response:");
      Serial.println(response);

    } else {

      Serial.print("Error Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  } else {

    Serial.println("WiFi Disconnected");
  }

  // Wait 10 seconds
  delay(10000);
}