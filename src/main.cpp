#include <FileSystem.h>

#define ONE_BIT_MODE false

void setup() {
    Serial.begin(115200);

    //Setting pins to work without resistors
    pinMode(2, INPUT_PULLUP);   
    pinMode(4, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(15, INPUT_PULLUP);

    if (!SD_MMC.begin("/sdcard", ONE_BIT_MODE)) {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD_MMC.cardType();

    if (cardType == CARD_NONE) {
        Serial.println("No SD_MMC card attached");
        return;
    }

    Serial.print("SD_MMC Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    writeFile(SD_MMC, "/gps-test.txt", "Beginning of the file\n");    
    appendFile(SD_MMC, "/gps-test.txt", "Hello World!\n");

    Serial.println("Done!");
}

void loop() {
}