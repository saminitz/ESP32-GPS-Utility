#ifndef __MYGPS_H__
#define __MYGPS_H__

#include <GPX.h>
#include <TinyGPS++.h>

class MyGPS {
   public:
    void setup();
    void loop();
    void smartDelay(unsigned long start, unsigned long ms);
    void waitForFix();
    const char* getDateTimeAsString(bool replaceColonWithDot = false);
    const char* getFixMode();
    const char* generateStats();
};

extern MyGPS myGPS;
#endif  // __MYGPS_H__