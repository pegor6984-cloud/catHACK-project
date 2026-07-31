#ifndef StorageManager_h
#define StorageManager_h

#include <Arduino.h>
#include <SD.h>
#include <LittleFS.h>
#include <vector>
#include "Globals.h"  // теперь все глобальные типы и объекты

// ============================================================
//  ХРАНИЛИЩЕ (режимы и переменные)
// ============================================================
enum StorageMode { STORAGE_SD, STORAGE_LITTLEFS };

extern StorageMode storageMode;
extern String storageCurrentPath;
extern std::vector<String> storageItems;
extern int storageSelectedIdx;
extern int storageActionIdx;
extern int storageCopyTarget;
extern String storageSelectedFile;
extern bool storageCopyMoveMode;

// ============================================================
//  ФУНКЦИИ ФАЙЛОВОГО МЕНЕДЖЕРА
// ============================================================
void listDirectory(String path, bool useSD, std::vector<String>& items);
void drawStorageBrowser();
void drawStorageAction();
void drawStorageCopyMove();
void handleRename();

bool deleteFile(String path, bool useSD);
bool renameFile(String oldPath, String newPath, bool useSD);
bool copyFile(String srcPath, String dstPath, bool srcSD, bool dstSD);
bool moveFile(String srcPath, String dstPath, bool srcSD, bool dstSD);

#endif