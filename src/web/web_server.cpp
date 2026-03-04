#include <web/web_server.h>

#include <Arduino.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <time.h>

#include <appState.h>
#include <config.h>

bool isValidTimeFormat(String timeStr);

static WebServer server(SERVER_PORT);

static void handleRoot()
{
    File file = LittleFS.open("/index.html", "r");
    if (!file)
    {
        server.send(500, "text/plain", "Error read index.html");
        return;
    }

    server.streamFile(file, "text/html");
    file.close();
}

static void handleOn()
{
    appState.ledOn = true;
    digitalWrite(LED_PIN, HIGH);
    handleRoot();
}

static void handleOff()
{
    appState.ledOn = false;
    digitalWrite(LED_PIN, LOW);
    handleRoot();
}

static void handleApi()
{
    DynamicJsonDocument doc(1024);
    
    doc["ledState"] = appState.ledOn;
    doc["currentTime"] = appState.currentTime;
    doc["timeOn"] = appState.timeOn;
    doc["timeOff"] = appState.timeOff;
    
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
}

void handleNotFound()
{
    server.send(404, "text/plain", "404: Страница не найдена");
}

void serveCSS() 
{
    File file = LittleFS.open("/css/style.css", "r");
    if (!file) { server.send(404, "text/plain", "Not found"); return; }
    server.streamFile(file, "text/css");
    file.close();
}

void serveJS() 
{
    File file = LittleFS.open("/js/script.js", "r");
    if (!file) { server.send(404, "text/plain", "Not found"); return; }
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleSendText() 
{
    if (server.hasArg("value1") && server.hasArg("value2"))
    {
        String timeOn = server.arg("value1");
        String timeOff = server.arg("value2");
        struct tm tmOn = {0}, tmOff = {0};

        if (isValidTimeFormat(timeOn) && isValidTimeFormat(timeOff)) 
        {
            strptime(timeOn.c_str(), "%H:%M:%S", &tmOn);
            strptime(timeOff.c_str(), "%H:%M:%S", &tmOff);

            appState.timeOn = timeOn;
            appState.timeOff = timeOff;

            prefs.putString("timeOn", timeOn);
            prefs.putString("timeOff", timeOff);

            Serial.println("Saved!");
        }

        server.send(200, "text/plain", "OK");
    } 
    else 
    {
        server.send(400, "text/plain", "No value");
    }
}

void webInit()
{
    server.on("/css/style.css", serveCSS);
    server.on("/js/script.js", serveJS);

    server.on("/sendText", handleSendText);

    server.on("/", handleRoot);
    server.on("/on", handleOn);
    server.on("/off", handleOff);
    server.on("/api", handleApi);
    server.onNotFound(handleNotFound);

    server.begin();
}

void webLoop()
{
    server.handleClient();
}

bool isValidTimeFormat(String timeStr) 
{
    struct tm tmStruct = {0};
    const char* timePtr = timeStr.c_str();
    
    if (strptime(timePtr, "%H:%M:%S", &tmStruct) != NULL) 
    {
        if (tmStruct.tm_hour >= 0 && tmStruct.tm_hour <= 23 &&
            tmStruct.tm_min >= 0 && tmStruct.tm_min <= 59 &&
            tmStruct.tm_sec >= 0 && tmStruct.tm_sec <= 59) 
            {
                return true;
            }
    }
    return false;
}