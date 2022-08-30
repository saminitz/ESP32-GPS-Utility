#ifndef __GPX_H__
#define __GPX_H__

#include <FileSystem.h>

class GPX {
   public:
    void setup();
    void reuseLastGpxOrCreateNew(const char* currentDateTime);
    void createNewGpxFile(const char* currentDateTime);
    void writeEndOfFile();
    const char* createNewTrackPoint(double latitude, double longitude, const char* time, const char* fix, double hdop, double speed);
    void appendCurrentGpxFile(const char* str);
};
#endif  // __GPX_H__