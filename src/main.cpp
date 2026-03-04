#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <LittleFS.h>
#include <time.h>
#include <Preferences.h>

#include <appState.h>
#include <config.h>
#include <web/web_server.h>
#include<UpdateTime/updateTime.h>

Preferences prefs;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n=== ESP32-C3 ВЕБ-СЕРВЕР ===");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  prefs.begin("settings", false);

  WiFiManager wm;
  //wm.setSaveConfigCallback(saveConfigCallback);
  //wm.resetSettings();
  bool connected = wm.autoConnect("ESP32-C3-Config", "12345678");
  
  if(!connected) 
  {
    Serial.println("Не удалось подключиться к Wi-Fi");
    delay(10000);
    ESP.restart();
  }
  
  if (!LittleFS.begin(true)) 
  {
    Serial.println("Ошибка LittleFS");
    return;
  }

  initTime();

  Serial.print(" IP адрес: http://");
  Serial.println(WiFi.localIP());

  webInit();
  Serial.println(" Веб-сервер запущен!");

  appState.timeOn = prefs.getString("timeOn", "00:00:00");
  appState.timeOff = prefs.getString("timeOff", "23:59:59");


}

void loop()
{
  delay(10);
  webLoop();
  if(!updateTime()) return;

  int nowSec  = getCurrentSeconds();
  int onSec   = timeToSeconds(appState.timeOn);
  int offSec  = timeToSeconds(appState.timeOff);
  bool ledActive = isTimeInRange(nowSec, onSec, offSec);

  digitalWrite(LED_PIN, ledActive ? LOW : HIGH); //TODO
}