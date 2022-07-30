#include <FileSystem.h>

FileSystem sdcard;

void setup() {
    Serial.begin(115200);

    sdcard.setup();

    sdcard.writeFile(SD_MMC, "/gps-test.txt", "Beginning of the file\n");    
    sdcard.appendFile(SD_MMC, "/gps-test.txt", "Hello World!\n");

    Serial.println("Done!");
}

void loop() {
}