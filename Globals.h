#ifndef Globals_h
#define Globals_h

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// ============================================================
//  КОНСТАНТЫ ДИСПЛЕЯ
// ============================================================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SSD1306_WHITE 1
#define SSD1306_BLACK 0
#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

// ============================================================
//  ГЛОБАЛЬНЫЕ ОБЪЕКТЫ (extern)
// ============================================================
extern Adafruit_SSD1306 display;
extern bool needRedraw;
extern String statusMsg;
extern unsigned long statusMsgTime;
extern String lastLongMsg;
extern int msgScrollOffset;
extern unsigned long lastMsgScrollTime;
extern int SD_CS_PIN;
extern String storageNewName;

// ============================================================
//  ВСЕ СОСТОЯНИЯ ПРИЛОЖЕНИЯ (AppState)
// ============================================================
enum AppState {
  STATE_STORAGE_BROWSER,      // просмотр файлов/папок
  STATE_STORAGE_ACTION,       // меню действий с файлом
  STATE_STORAGE_RENAME,       // ввод нового имени
  STATE_STORAGE_COPY_MOVE,    // выбор места назначения (SD/LittleFS)
  STATE_RFID_MENU,
  STATE_RFID_CONFIG,
  STATE_RFID_CONFIG_MODULE,
  STATE_RFID_CONFIG_PROTOCOL,
  STATE_RFID_CONFIG_PINS,
  STATE_RFID_CONFIG_PINS_VALUE,
  STATE_RFID_SCAN,
  STATE_RFID_EMULATE,
  STATE_LAUNCHER,
  STATE_AUDIO_MENU,
  STATE_AUDIO_VOLUME,
  STATE_APPS_MENU,
  STATE_APPS_WIKIPEDIA_INPUT,
  STATE_APPS_WIKIPEDIA_RESULT,
  STATE_APPS_CALCULATOR,
  STATE_APPS_GAME1,
  STATE_APPS_GAME2,
  STATE_BLUETOOTH_SCAN,
  STATE_BLUETOOTH_MENU,
  STATE_LED_SELECT_DEVICE,
  STATE_LED_MAIN_MENU,
  STATE_LED_COLOR_MENU,
  STATE_LED_EFFECT_MENU,
  STATE_LED_BRIGHTNESS_MENU,
  STATE_LED_TIMEOUT_MENU,
  STATE_CONFIRM_FACTORY_RESET,
  STATE_MAIN_MENU,
  STATE_WIFI_MENU,
  STATE_WIFI_SCAN,
  STATE_WIFI_SPECTRUM,
  STATE_WIFI_ACTIONS,
  STATE_WIFI_INFO,
  STATE_NRF24_MENU,
  STATE_NRF24_SPECTRUM,
  STATE_NRF24_JAMMER,
  STATE_IR_MENU,
  STATE_IR_CAPTURE,
  STATE_IR_TRANSMIT,
  STATE_IR_ERASE,
  STATE_TVBGONE,
  STATE_SETTINGS_MENU,
  STATE_SYSTEM_INFO,
  STATE_TIMEOUT,
  STATE_RESET_CONFIRM,
  STATE_REBOOT_CONFIRM,
  STATE_FACTORY_RESET_CONFIRM,
  STATE_CONSOLE,
  STATE_CONSOLE_COMMAND_OUTPUT,
  STATE_WIFI_CONNECTING,
  STATE_WIFI_CHAT,
  STATE_CC1101_SCAN_COPY,
  STATE_CC1101_MENU,
  STATE_CC1101_SPECTRUM_VERT,
  STATE_CC1101_SPECTRUM_HORIZ,
  STATE_CC1101_JAMMER,
  STATE_CC1101_CAPTURE,
  STATE_CC1101_TRANSMIT,
  STATE_BADUSB_MENU,
  STATE_BADUSB_BUILTIN,
  STATE_BADUSB_SD,
  STATE_EVIL_PORTAL,
  STATE_DEAUTHER,
  STATE_NRF_ENHANCED
};

extern AppState appState;

// ============================================================
//  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ (extern)
// ============================================================
extern void drawHeader(const char* title);
extern void drawTopBarIcons();
extern void showMsg(const char* msg);
extern String inputStringWithKeyboard(bool allowExit, const char* title);

#endif