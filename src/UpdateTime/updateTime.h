#pragma once
#include <Arduino.h>

String getTime();
bool updateTime();
void initTime();
int timeToSeconds(const String& );
int getCurrentSeconds();
bool isTimeInRange(int, int, int);