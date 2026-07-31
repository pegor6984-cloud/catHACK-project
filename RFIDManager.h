#ifndef RFIDManager_h
#define RFIDManager_h

#include <Arduino.h>
#include <Preferences.h>
#include <SPI.h>
#include <Wire.h>

#include <MFRC522.h>
#include <Adafruit_PN532.h>

#define MAX_SAVED_CARDS 10

class RFIDManager {
public:
    enum Module { MODULE_NONE, MODULE_RC522, MODULE_PN532 };
    enum Protocol { PROTOCOL_SPI, PROTOCOL_I2C };

    struct PinConfig {
        int sck, miso, mosi, cs, rst; // для SPI
        int sda, scl;                 // для I2C
    };

    RFIDManager();
    void begin();
    void update();

    Module getModule();
    void setModule(Module m);
    Protocol getProtocol();
    void setProtocol(Protocol p);

    PinConfig getPins(Module m);
    void setPins(Module m, PinConfig pins);

    bool scanCard(String &uidStr, String &data);
    bool saveCard(String uidStr, String data = "");
    int getSavedCardsCount();
    String getSavedUID(int index);
    bool deleteSavedCard(int index);
    bool clearSavedCards();

    bool emulateCard(int index);
    void stopEmulate();

private:
    Preferences pref;
    Module currentModule;
    Protocol currentProtocol;
    PinConfig pinsRC522;
    PinConfig pinsPN532;
    String savedCards[MAX_SAVED_CARDS];
    int savedCount;

    MFRC522 *mfrc522;
    Adafruit_PN532 *pn532;
    bool initialized;

    void loadSettings();
    void saveSettings();
    void initModule();
    void deinitModule();
    void initRC522();
    void initPN532_SPI();
    void initPN532_I2C();
};

#endif