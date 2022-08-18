#include "GPX.h"

FileSystem sdcard;
const char* currentFile;

void GPX::setup() {
    sdcard.setup();
}

void GPX::reuseLastGpxOrCreateNew(const char* currentDateTime) {
    const char* latestFile = sdcard.getNameOfLatestFileInFolder("/");
    if (latestFile == NULL)
        currentFile = currentDateTime;
    else
        currentFile = latestFile;
}



void GPX::createNewGpxFile(const char* currentDateTime) {
    currentFile = currentDateTime;
    String xmlBeginning =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<gpx xmlns=\"http://www.topografix.com/GPX/1/1\" version=\"1.1\" creator=\"https://github.com/juanirache/gopro-telemetry\">"
        "	<trk>"
        "		<name>" +
        (String)currentFile +
        "</name>"
        "		<desc>10Hz GPS (Lat., Long., Alt., 2D speed) - [deg,deg,m,m/s]</desc>"
        "		<src>ESP32 10Hz GPS</src>"
        "		<trkseg>";

    sdcard.writeFile(currentFile, xmlBeginning.c_str());
}

void GPX::writeEndOfFile() {
    const char* xmlEnding =
        "		</trkseg>"
        "	</trk>"
        "</gpx>";

    sdcard.writeFile(currentFile, xmlEnding);
}

const char* GPX::createNewTrackPoint(double latitude, double longitude, double altitude, const char* time, const char* fix, int hdop, double speed) {
    char* trkpt = new char[198];
    sprintf(trkpt,
            "			<trkpt lat=\"%0.8f\" lon=\"%0.8f\">\n"
            "				<ele>%0.3f</ele>\n"
            "				<time>%s</time>\n"
            "				<fix>%s</fix>\n"
            "				<hdop>%d</hdop>\n"
            "				<cmt>2dSpeed: %0.3f</cmt>\n"
            "			</trkpt>\n",
            latitude, longitude, altitude, time, fix, hdop, speed);
    
    return trkpt;
}

void GPX::appendCurrentGpxFile(const char* str) {
    sdcard.appendFile(currentFile, str);
}
