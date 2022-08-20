#include "GPX.h"

FileSystem sdcard;
static const char* currentFile;

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
    static char buf[32];
    sprintf(buf, "/%s.gpx", currentDateTime);

    currentFile = buf;
    String xmlBeginning =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<gpx xmlns=\"http://www.topografix.com/GPX/1/1\" version=\"1.1\" creator=\"https://github.com/juanirache/gopro-telemetry\">\n"
        "	<trk>\n"
        "		<name>" +
        (String)currentDateTime +
        "</name>\n"
        "		<desc>10Hz GPS (Lat., Long., Alt., 2D speed) - [deg,deg,m,m/s]</desc>\n"
        "		<src>ESP32 10Hz GPS</src>\n"
        "		<trkseg>\n";

    sdcard.writeFile(currentFile, xmlBeginning.c_str());
}

void GPX::writeEndOfFile() {
    const char* xmlEnding =
        "		</trkseg>\n"
        "	</trk>\n"
        "</gpx>";

    sdcard.writeFile(currentFile, xmlEnding);
}

const char* GPX::createNewTrackPoint(double latitude, double longitude, double altitude, const char* time, const char* fix, int hdop, int speed) {
    static char trkpt[200];
    sprintf(trkpt,
            "			<trkpt lat=\"%0.8f\" lon=\"%0.8f\">\n"
            "				<ele>%0.3f</ele>\n"
            "				<time>%s</time>\n"
            "				<fix>%s</fix>\n"
            "				<hdop>%d</hdop>\n"
            "				<cmt>2dSpeed: %d</cmt>\n"
            "			</trkpt>\n",
            latitude, longitude, altitude, time, fix, hdop, speed);

    return trkpt;
}

void GPX::appendCurrentGpxFile(const char* str) {
    sdcard.appendFile(currentFile, str);
}
