#include <appState.h>

unsigned long lastTimeUpdate = 0;
const unsigned long timeUpdateInterval = 10000;


String getTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) 
    {
        return "Error";
    }
    
    char timeString[64];
    strftime(timeString, sizeof(timeString), "%d.%m.%Y %H:%M:%S", &timeinfo);
    
    return String(timeString);
}

bool updateTime() 
{
    bool update = false;
    if (millis() - lastTimeUpdate >= timeUpdateInterval) 
    {
        lastTimeUpdate = millis();
        
        appState.currentTime = getTime();
        update = true;
    }
    return update;
}

void initTime() 
{
    configTime(4 * 3600, 0, "pool.ntp.org");

    appState.currentTime = getTime();
}

int timeToSeconds(const String& timeStr)
{
    struct tm tmStruct = {0};
    if (strptime(timeStr.c_str(), "%H:%M:%S", &tmStruct))
    {
        return tmStruct.tm_hour * 3600 +
               tmStruct.tm_min * 60 +
               tmStruct.tm_sec;
    }
    return 0;
}

int getCurrentSeconds()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
        return 0;

    return timeinfo.tm_hour * 3600 +
           timeinfo.tm_min * 60 +
           timeinfo.tm_sec;
}

bool isTimeInRange(int now, int onTime, int offTime)
{
    if (onTime <= offTime)
    {
        return now >= onTime && now < offTime;
    }
    else
    {
        return now >= onTime || now < offTime;
    }
}