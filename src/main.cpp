#include <FileSystem.h>
#include <WebServer.h>

FileSystem sdcard;
WebServer webServer;

void setup() {
    Serial.begin(115200);

    webServer.setup();

    sdcard.setup();

    sdcard.writeFile(SD_MMC, "/gps-test.txt", "Beginning of the file\n");    
    sdcard.appendFile(SD_MMC, "/gps-test.txt", "Hello World!\n");

    Serial.println("Done!");
}

void loop() {
}