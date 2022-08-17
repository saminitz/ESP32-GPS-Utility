#ifndef __GPX_H__
#define __GPX_H__

#include <FileSystem.h>
#include <MyGPS.h>

class GPX {
   public:
    void setup();
    void reuseLastGPX(const char* currentDateTime);
    void createNewGpxFile();
    void writeEndOfFile();
    const char* createNewTrackPoint(double latitude, double longitude, double altitude, const char* time, const char* fix, int hdop, double speed);
    void appendCurrentGpxFile(const char* str);
};
#endif  // __GPX_H__