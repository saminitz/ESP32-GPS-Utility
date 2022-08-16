#include "MyGPS.h"

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 230400;

TinyGPSPlus gps;

void MyGPS::setup() {
    Serial2.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
}

void MyGPS::loop() {
    unsigned long start = millis();



    smartDelay(start, 95);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
void MyGPS::smartDelay(unsigned long start, unsigned long ms) {
    do {
        while (Serial2.available())
            gps.encode(Serial2.read());
    } while (millis() - start < ms);
}

String MyGPS::getDateTimeAsString() {
    TinyGPSDate d = gps.date;
    TinyGPSTime t = gps.time;
    char dateTime[25];

    sprintf(dateTime, "%04d-%02d-%2dT%02d:%02d:%02d.%03dZ", d.year(), d.month(), d.day(),
            t.hour(), t.minute(), t.second(),
            t.centisecond() * 10 + (int)(millis() % 100));  // milliseconds of the esp32 smuggled in to get to time

    return dateTime;
}