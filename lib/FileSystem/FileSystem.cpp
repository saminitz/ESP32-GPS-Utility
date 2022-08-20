/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      14
 *    VSS      GND
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */

#include "FileSystem.h"

#define ONE_BIT_MODE false

void FileSystem::setup() {
    // Setting pins to work without resistors
    pinMode(2, INPUT_PULLUP);
    // pinMode(4, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(15, INPUT_PULLUP);

    if (!SD_MMC.begin("/sdcard", ONE_BIT_MODE)) {
        Serial.println("Card Mount Failed");
        delay(INT32_MAX);
        return;
    }
    uint8_t cardType = SD_MMC.cardType();

    if (cardType == CARD_NONE) {
        Serial.println("No SD_MMC card attached");
        delay(INT32_MAX);
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
}

void FileSystem::listDir(const char *dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\n", dirname);

    File root = SD_MMC.open(dirname);
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(file.name(), levels - 1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

const char *FileSystem::getNameOfLatestFileInFolder(const char *dirname) {
    File root = SD_MMC.open(dirname);
    if (!root) {
        Serial.println("Failed to open directory");
        return NULL;
    }
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return NULL;
    }

    File file = root.openNextFile();
    File lastFile = file;
    while (file) {
        file = root.openNextFile();
        lastFile = file;
    }

    return !lastFile ? NULL : lastFile.name();
}

void FileSystem::createDir(const char *path) {
    if (SD_MMC.mkdir(path)) {
        Serial.printf("Created Dir: %s\n", path);
    } else {
        Serial.printf("mkdir failed on dir %s\n", path);
    }
}

void FileSystem::removeDir(const char *path) {
    if (SD_MMC.rmdir(path)) {
        Serial.printf("Removed Dir: %s\n", path);
    } else {
        Serial.printf("rmdir failed on file %s\n", path);
    }
}

void FileSystem::readFile(const char *path) {
    Serial.printf("Reading file: %s\n", path);

    File file = SD_MMC.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while (file.available()) {
        Serial.write(file.read());
    }
}

void FileSystem::writeFile(const char *path, const char *message) {
    File file = SD_MMC.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        Serial.printf("Overwritten file: %s\n", path);
    } else {
        Serial.printf("Writing file failed: %s\n", path);
    }
}

void FileSystem::appendFile(const char *path, const char *message) {
    File file = SD_MMC.open(path, FILE_APPEND);
    if (!file) {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message)) {
        // Serial.printf("Appended to file: %s\n", path);
    } else {
        Serial.printf("Appending to file failed: %s\n", path);
    }
}

void FileSystem::renameFile(const char *path1, const char *path2) {
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (SD_MMC.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void FileSystem::deleteFile(const char *path) {
    Serial.printf("Deleting file: %s\n", path);
    if (SD_MMC.remove(path)) {
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void FileSystem::testFileIO(const char *path) {
    File file = SD_MMC.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if (file) {
        len = file.size();
        size_t flen = len;
        start = millis();
        while (len) {
            size_t toRead = len;
            if (toRead > 512) {
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }

    file = SD_MMC.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for (i = 0; i < 2048; i++) {
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}