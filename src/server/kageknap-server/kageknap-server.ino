#include <WiFi.h>
#include <WiFiMulti.h>

// https://github.com/evert-arias/EasyButton
#include <EasyButton.h>
// https://github.com/jandelgado/jled
#include <jled.h>
// https://github.com/contrem/arduino-timer
#include <timer.h>
// https://github.com/adafruit/Adafruit_MQTT_Library
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// https://github.com/contrem/arduino-timer
#include <timer.h>

#include "secret.h"

WiFiMulti wifiMulti;
auto led = JLed(27).Breathe(2500).DelayAfter(1500).Forever();
auto timer = timer_create_default();
EasyButton button(21);


bool function_to_call(void *argument) {    
    led = JLed(27).Breathe(2500).DelayAfter(1500).Forever();        
    return true; 
}

void setup() {

  Serial.begin(115200);
  delay(100);
  
  Serial.println("---- setup start");

  pinMode(27, OUTPUT);
  pinMode(21, INPUT);
  
  Serial.println("Wifi connect");  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  wifiMulti.addAP(const_ssid1, const_password1);
  wifiMulti.addAP(const_ssid2, const_password2);  
  while (wifiMulti.run() != WL_CONNECTED) { 
    Serial.print('.');
    delay(500);    
  }
  
  Serial.println("WiFi connected");
  Serial.println("SSIP: ");
  Serial.println(WiFi.SSID());
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  button.onPressed(onPressed);
  
  Serial.println("---- setup end");
}


void onPressed() {
  Serial.println("Button has been pressed!");
  delay(100);
  led =  JLed(27).Blink(300, 300).Forever();    
  timer.in(5000, function_to_call); 
}



void loop() {
  led.Update();
  button.read();
  timer.tick();
  yield();
}
