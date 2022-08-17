#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <FS.h>
#include <SD_MMC.h>

#define ONE_BIT_MODE false

class FileSystem {
   public:
    void setup();
    void listDir(const char *dirname, uint8_t levels);
    const char*  getNameOfLatestFileInFolder(const char *dirname);
    void createDir(const char *path);
    void removeDir(const char *path);
    void readFile(const char *path);
    void writeFile(const char *path, const char *message);
    void appendFile(const char *path, const char *message);
    void renameFile(const char *path1, const char *path2);
    void deleteFile(const char *path);
    void testFileIO(const char *path);
};
#endif  // __FILESYSTEM_H__