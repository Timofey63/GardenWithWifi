#pragma once
#include <Arduino.h>

struct AppState {
    bool ledOn;
    bool wifiConnected;
    IPAddress ip;
    String currentTime;
    String timeOff, timeOn;
};

extern AppState appState;