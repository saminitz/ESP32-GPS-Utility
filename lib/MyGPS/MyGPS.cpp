#include "MyGPS.h"

static const int RXPin = 16, TXPin = 17;
static const int GPSHz = 10;
static const int GPSPeriod = (1 / (double)GPSHz) * 1000;
static const uint32_t GPSBaud = 230400;

TinyGPSPlus gps;
TinyGPSCustom fixMode(gps, "GNGSA", 2);

GPX gpx;

void MyGPS::setup() {
    Serial2.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

    gpx.setup();
    waitForFix();

    gpx.createNewGpxFile(getDateTimeAsString(true));
}

void MyGPS::loop() {
    unsigned long start = millis();

    if (!(gps.location.isValid() && gps.date.isValid() && gps.time.isValid() && fixMode.isValid() && fixMode.value() != "1" && gps.hdop.isValid() && gps.speed.isValid())) {
        smartDelay(start, GPSPeriod);
        return;
    }

    Serial.println("Valid");

    gpx.appendCurrentGpxFile(gpx.createNewTrackPoint(
        gps.location.lat(),
        gps.location.lng(),
        getDateTimeAsString(),
        fixMode.value() == "2" ? "2d" : fixMode.value() == "3" ? "3d"
                                                               : fixMode.value(),
        gps.hdop.value(),
        gps.speed.kmph()));

    smartDelay(start, GPSPeriod);
}

// This custom version of delay() ensures that the gps object
// is being "fed".
void MyGPS::smartDelay(unsigned long start, unsigned long ms) {
    do {
        while (Serial2.available())
            gps.encode(Serial2.read());
    } while (millis() - start < ms);
}

void MyGPS::waitForFix() {
    Serial.println("Waiting first fix");
    while (!gps.location.isValid()) {
        smartDelay(millis(), 100);
    }
    Serial.println("Found fist fix");
}

const char* MyGPS::getFixMode() {
    return fixMode.value();
}

const char* MyGPS::getDateTimeAsString(bool replaceColonWithDot) {
    TinyGPSDate d = gps.date;
    TinyGPSTime t = gps.time;
    static char dateTime[25];
    char timeSpacer = replaceColonWithDot ? '.' : ':';

    sprintf(dateTime, "%04d-%02d-%2dT%02d%c%02d%c%02d.%03dZ", d.year(), d.month(), d.day(),
            t.hour(), timeSpacer, t.minute(), timeSpacer, t.second(),
            t.centisecond() * 10 + (int)(millis() % 100));  // milliseconds of the esp32 smuggled in to get to time

    return dateTime;
}