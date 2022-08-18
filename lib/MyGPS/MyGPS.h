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
    const char* getDateTimeAsString();
};
#endif  // __MYGPS_H__