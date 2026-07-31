#include "StorageManager.h"
#include "Globals.h"   // для display, WHITE, BLACK, SCREEN_WIDTH и extern-функций

// ============================================================
//  ОПРЕДЕЛЕНИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ ХРАНИЛИЩА
// ============================================================
StorageMode storageMode = STORAGE_SD;
String storageCurrentPath = "/";
std::vector<String> storageItems;
int storageSelectedIdx = 0;
int storageActionIdx = 0;
int storageCopyTarget = 0;
String storageSelectedFile = "";
bool storageCopyMoveMode = false;

// ============================================================
//  РЕАЛИЗАЦИЯ
// ============================================================

void listDirectory(String path, bool useSD, std::vector<String>& items) {
    items.clear();
    File root;
    if (useSD) {
        if (!SD.begin(SD_CS_PIN)) return;
        root = SD.open(path);
    } else {
        if (!LittleFS.begin(true)) return;
        root = LittleFS.open(path);
    }
    if (!root) return;
    if (!root.isDirectory()) return;

    File file = root.openNextFile();
    while (file) {
        String name = String(file.name());
        if (file.isDirectory()) name = "/" + name;
        items.push_back(name);
        file = root.openNextFile();
    }
    root.close();

    std::sort(items.begin(), items.end(), [](const String& a, const String& b) {
        bool aDir = a.startsWith("/");
        bool bDir = b.startsWith("/");
        if (aDir && !bDir) return true;
        if (!aDir && bDir) return false;
        return a < b;
    });
    items.push_back("Back");
}

void drawStorageBrowser() {
    display.clearDisplay();
    drawHeader("Storage");

    listDirectory(storageCurrentPath, storageMode == STORAGE_SD, storageItems);

    int total = storageItems.size();
    if (storageSelectedIdx < 0) storageSelectedIdx = total - 1;
    if (storageSelectedIdx >= total) storageSelectedIdx = 0;

    int visible = 4;
    int offset = 0;
    if (storageSelectedIdx >= visible) offset = storageSelectedIdx - visible + 1;
    if (offset < 0) offset = 0;
    if (offset + visible > total) offset = total - visible;
    if (offset < 0) offset = 0;

    for (int i = 0; i < visible; i++) {
        int idx = offset + i;
        if (idx >= total) break;
        int y = 14 + i * 10;
        if (idx == storageSelectedIdx) {
            display.fillRect(0, y-1, SCREEN_WIDTH, 10, WHITE);
            display.setTextColor(BLACK);
            display.setCursor(4, y);
            display.print(">");
        } else {
            display.setTextColor(WHITE);
        }
        display.setCursor(14, y);
        String label = storageItems[idx];
        if (label.length() > 18) label = label.substring(0, 16) + "..";
        display.print(label);
    }

    display.setCursor(2, 56);
    display.print(offset+1); display.print("/"); display.print(total);
    display.setCursor(70, 56);
    display.print(storageMode == STORAGE_SD ? "SD" : "FS");
    display.print(": ");
    String shortPath = storageCurrentPath;
    if (shortPath.length() > 8) shortPath = "..." + shortPath.substring(shortPath.length()-8);
    display.print(shortPath);

    drawTopBarIcons();
    display.display();
}

void drawStorageAction() {
    display.clearDisplay();
    char title[30];
    snprintf(title, sizeof(title), "Action: %s", storageSelectedFile.c_str());
    drawHeader(title);

    const char* actions[] = { "Delete", "Rename", "Copy", "Move", "Back" };
    int total = 5;
    if (storageActionIdx < 0) storageActionIdx = total - 1;
    if (storageActionIdx >= total) storageActionIdx = 0;

    for (int i = 0; i < total; i++) {
        int y = 14 + i * 10;
        if (i == storageActionIdx) {
            display.fillRect(0, y-1, SCREEN_WIDTH, 10, WHITE);
            display.setTextColor(BLACK);
            display.setCursor(4, y);
            display.print(">");
        } else {
            display.setTextColor(WHITE);
        }
        display.setCursor(14, y);
        display.print(actions[i]);
    }
    drawTopBarIcons();
    display.display();
}

void drawStorageCopyMove() {
    display.clearDisplay();
    drawHeader("Copy/Move to");
    const char* targets[] = { "SD Card", "Internal FS", "Back" };
    int total = 3;
    if (storageCopyTarget < 0) storageCopyTarget = total - 1;
    if (storageCopyTarget >= total) storageCopyTarget = 0;

    for (int i = 0; i < total; i++) {
        int y = 14 + i * 10;
        if (i == storageCopyTarget) {
            display.fillRect(0, y-1, SCREEN_WIDTH, 10, WHITE);
            display.setTextColor(BLACK);
            display.setCursor(4, y);
            display.print(">");
        } else {
            display.setTextColor(WHITE);
        }
        display.setCursor(14, y);
        display.print(targets[i]);
    }
    drawTopBarIcons();
    display.display();
}

void handleRename() {
    storageNewName = inputStringWithKeyboard(true, "New name:");
    if (storageNewName.length() > 0) {
        String oldPath = storageCurrentPath + storageSelectedFile;
        String newPath = storageCurrentPath + storageNewName;
        bool ok = renameFile(oldPath, newPath, storageMode == STORAGE_SD);
        showMsg(ok ? "Renamed" : "Rename failed");
    }
    appState = STATE_STORAGE_BROWSER;
    needRedraw = true;
}

bool deleteFile(String path, bool useSD) {
    if (useSD) {
        if (!SD.begin(SD_CS_PIN)) return false;
        return SD.remove(path);
    } else {
        if (!LittleFS.begin(true)) return false;
        return LittleFS.remove(path);
    }
}

bool renameFile(String oldPath, String newPath, bool useSD) {
    if (useSD) {
        if (!SD.begin(SD_CS_PIN)) return false;
        return SD.rename(oldPath, newPath);
    } else {
        if (!LittleFS.begin(true)) return false;
        return LittleFS.rename(oldPath, newPath);
    }
}

bool copyFile(String srcPath, String dstPath, bool srcSD, bool dstSD) {
    File src;
    if (srcSD) {
        if (!SD.begin(SD_CS_PIN)) return false;
        src = SD.open(srcPath, FILE_READ);
    } else {
        if (!LittleFS.begin(true)) return false;
        src = LittleFS.open(srcPath, FILE_READ);
    }
    if (!src) return false;

    File dst;
    if (dstSD) {
        if (!SD.begin(SD_CS_PIN)) { src.close(); return false; }
        dst = SD.open(dstPath, FILE_WRITE);
    } else {
        if (!LittleFS.begin(true)) { src.close(); return false; }
        dst = LittleFS.open(dstPath, FILE_WRITE);
    }
    if (!dst) { src.close(); return false; }

    uint8_t buffer[512];
    while (src.available()) {
        size_t bytesRead = src.read(buffer, sizeof(buffer));
        dst.write(buffer, bytesRead);
    }
    dst.close();
    src.close();
    return true;
}

bool moveFile(String srcPath, String dstPath, bool srcSD, bool dstSD) {
    if (srcSD == dstSD) {
        return renameFile(srcPath, dstPath, srcSD);
    } else {
        if (copyFile(srcPath, dstPath, srcSD, dstSD)) {
            return deleteFile(srcPath, srcSD);
        }
        return false;
    }
}