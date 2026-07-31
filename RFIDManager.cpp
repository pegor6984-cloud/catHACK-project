#include "RFIDManager.h"

RFIDManager::RFIDManager() {
    mfrc522 = nullptr;
    pn532 = nullptr;
    initialized = false;
    currentModule = MODULE_NONE;
    currentProtocol = PROTOCOL_SPI;
    savedCount = 0;

    pinsRC522 = {48, 34, 38, 45, 46};   // SCK=48, MISO=34, MOSI=38, CS=45, RST=46
    pinsPN532 = {21, 33, 38, 45, -1};
    pinsPN532.sda = 47;
    pinsPN532.scl = 48;
}

void RFIDManager::begin() {
    loadSettings();
    initModule();
}

void RFIDManager::update() {}

RFIDManager::Module RFIDManager::getModule() { return currentModule; }
void RFIDManager::setModule(Module m) {
    if (currentModule != m) {
        currentModule = m;
        deinitModule();
        initModule();
        saveSettings();
    }
}

RFIDManager::Protocol RFIDManager::getProtocol() { return currentProtocol; }
void RFIDManager::setProtocol(Protocol p) {
    if (currentProtocol != p) {
        currentProtocol = p;
        deinitModule();
        initModule();
        saveSettings();
    }
}

RFIDManager::PinConfig RFIDManager::getPins(Module m) {
    return (m == MODULE_RC522) ? pinsRC522 : pinsPN532;
}

void RFIDManager::setPins(Module m, PinConfig pins) {
    if (m == MODULE_RC522) pinsRC522 = pins;
    else pinsPN532 = pins;
    if (currentModule == m) {
        deinitModule();
        initModule();
    }
    saveSettings();
}

bool RFIDManager::scanCard(String &uidStr, String &data) {
    if (!initialized) return false;

    if (currentModule == MODULE_RC522) {
        if (!mfrc522) return false;
        if (!mfrc522->PICC_IsNewCardPresent()) return false;
        if (!mfrc522->PICC_ReadCardSerial()) return false;
        uidStr = "";
        for (byte i = 0; i < mfrc522->uid.size; i++) {
            if (uidStr.length() > 0) uidStr += " ";
            char buf[3];
            sprintf(buf, "%02X", mfrc522->uid.uidByte[i]);
            uidStr += buf;
        }
        data = "";
        mfrc522->PICC_HaltA();
        return true;
    }
    else if (currentModule == MODULE_PN532) {
        if (!pn532) return false;
        uint8_t uid[7];
        uint8_t uidLength;
        bool success = pn532->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 1000);
        if (!success) return false;
        uidStr = "";
        for (uint8_t i = 0; i < uidLength; i++) {
            if (uidStr.length() > 0) uidStr += " ";
            char buf[3];
            sprintf(buf, "%02X", uid[i]);
            uidStr += buf;
        }
        data = "";
        return true;
    }
    return false;
}

bool RFIDManager::saveCard(String uidStr, String data) {
    if (savedCount >= MAX_SAVED_CARDS) return false;
    for (int i = 0; i < savedCount; i++) {
        if (savedCards[i] == uidStr) return false;
    }
    savedCards[savedCount++] = uidStr;
    saveSettings();
    return true;
}

int RFIDManager::getSavedCardsCount() { return savedCount; }
String RFIDManager::getSavedUID(int index) {
    if (index >= 0 && index < savedCount) return savedCards[index];
    return "";
}
bool RFIDManager::deleteSavedCard(int index) {
    if (index < 0 || index >= savedCount) return false;
    for (int i = index; i < savedCount - 1; i++) savedCards[i] = savedCards[i+1];
    savedCount--;
    saveSettings();
    return true;
}
bool RFIDManager::clearSavedCards() {
    savedCount = 0;
    saveSettings();
    return true;
}

bool RFIDManager::emulateCard(int index) {
    // Заглушка для Adafruit PN532 (позже добавим)
    return false;
}

void RFIDManager::stopEmulate() {}

void RFIDManager::loadSettings() {
    pref.begin("rfid", true);
    currentModule = (Module)pref.getInt("module", MODULE_NONE);
    currentProtocol = (Protocol)pref.getInt("protocol", PROTOCOL_SPI);

    pinsRC522.sck   = pref.getInt("rc_sck", 21);
    pinsRC522.miso  = pref.getInt("rc_miso", 33);
    pinsRC522.mosi  = pref.getInt("rc_mosi", 38);
    pinsRC522.cs    = pref.getInt("rc_cs", 45);
    pinsRC522.rst   = pref.getInt("rc_rst", 46);

    pinsPN532.sck   = pref.getInt("pn_sck", 21);
    pinsPN532.miso  = pref.getInt("pn_miso", 33);
    pinsPN532.mosi  = pref.getInt("pn_mosi", 38);
    pinsPN532.cs    = pref.getInt("pn_cs", 45);
    pinsPN532.rst   = pref.getInt("pn_rst", -1);
    pinsPN532.sda   = pref.getInt("pn_sda", 47);
    pinsPN532.scl   = pref.getInt("pn_scl", 48);

    savedCount = pref.getInt("cardCount", 0);
    if (savedCount > MAX_SAVED_CARDS) savedCount = MAX_SAVED_CARDS;
    for (int i = 0; i < savedCount; i++) {
        savedCards[i] = pref.getString(("card" + String(i)).c_str(), "");
    }
    pref.end();
}

void RFIDManager::saveSettings() {
    pref.begin("rfid", false);
    pref.putInt("module", (int)currentModule);
    pref.putInt("protocol", (int)currentProtocol);
    pref.putInt("rc_sck", pinsRC522.sck);
    pref.putInt("rc_miso", pinsRC522.miso);
    pref.putInt("rc_mosi", pinsRC522.mosi);
    pref.putInt("rc_cs", pinsRC522.cs);
    pref.putInt("rc_rst", pinsRC522.rst);
    pref.putInt("pn_sck", pinsPN532.sck);
    pref.putInt("pn_miso", pinsPN532.miso);
    pref.putInt("pn_mosi", pinsPN532.mosi);
    pref.putInt("pn_cs", pinsPN532.cs);
    pref.putInt("pn_rst", pinsPN532.rst);
    pref.putInt("pn_sda", pinsPN532.sda);
    pref.putInt("pn_scl", pinsPN532.scl);
    pref.putInt("cardCount", savedCount);
    for (int i = 0; i < savedCount; i++) {
        pref.putString(("card" + String(i)).c_str(), savedCards[i]);
    }
    pref.end();
}

void RFIDManager::initModule() {
    deinitModule();
    if (currentModule == MODULE_RC522) {
        initRC522();
    } else if (currentModule == MODULE_PN532) {
        if (currentProtocol == PROTOCOL_SPI) initPN532_SPI();
        else if (currentProtocol == PROTOCOL_I2C) initPN532_I2C();
    }
    initialized = true;
}

void RFIDManager::deinitModule() {
    if (mfrc522) { delete mfrc522; mfrc522 = nullptr; }
    if (pn532) { delete pn532; pn532 = nullptr; }
    initialized = false;
}

void RFIDManager::initRC522() {
    SPI.begin(pinsRC522.sck, pinsRC522.miso, pinsRC522.mosi, pinsRC522.cs);
    mfrc522 = new MFRC522(pinsRC522.cs, pinsRC522.rst);
    mfrc522->PCD_Init();
}

void RFIDManager::initPN532_SPI() {
    SPI.begin(pinsPN532.sck, pinsPN532.miso, pinsPN532.mosi, pinsPN532.cs);
    pn532 = new Adafruit_PN532(pinsPN532.cs, &SPI);
    pn532->begin();
    uint32_t version = pn532->getFirmwareVersion();
    if (!version) {
        // Ошибка – не найдено
    }
}

void RFIDManager::initPN532_I2C() {
    Wire.begin(pinsPN532.sda, pinsPN532.scl);
    pn532 = new Adafruit_PN532(-1, -1, &Wire);
    pn532->begin();
    uint32_t version = pn532->getFirmwareVersion();
    if (!version) {
        // Ошибка – не найдено
    }
}