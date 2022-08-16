#ifndef __GPX_H__
#define __GPX_H__

#include <FileSystem.h>
#include <MyGPS.h>

class GPX {
   public:
    void setup();
    void createNewGpxFile();
    void appendCurrentGpxFile();
};
#endif  // __GPX_H__