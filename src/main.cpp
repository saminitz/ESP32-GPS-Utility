#include <FileSystem.h>

void setup() {
    Serial.begin(115200);

    FileSystemSetup();

    writeFile(SD_MMC, "/gps-test.txt", "Beginning of the file\n");    
    appendFile(SD_MMC, "/gps-test.txt", "Hello World!\n");

    Serial.println("Done!");
}

void loop() {
}