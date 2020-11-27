
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
const int SHORT_PRESS_TIME = 1000; // 500 milliseconds
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

const char* ssid = "fsociety";
const char* password = "freedom77";

 
void setup() {
  Serial.begin(9600);
  pinMode(D3, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  WiFi.begin(ssid, password);
}

void loop() {
  currentState = digitalRead(D3);

  if(lastState == HIGH && currentState == LOW)        // button is pressed
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if( pressDuration < SHORT_PRESS_TIME ) {
      if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
        HTTPClient http;  //Declare an object of class HTTPClient
 
        http.begin("http://jsonplaceholder.typicode.com/posts/1");  //Specify request destination
        int httpCode = http.GET();                                                                  //Send the request
 
        if (httpCode == 200) { //Check the returning code
            digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
            delay(3000);                       // wait for a second
            digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);   
        }
 
        http.end();   //Close connection
 
      }
    }
  }
  lastState = currentState;  
}
