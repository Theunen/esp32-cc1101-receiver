/*
  ESP32 (CH340 / NodeMCU-32S / WROOM-32 / ESP-WROOM-32) + CC1101 ontvanger
  Library: SmartRC-CC1101-Driver-Lib
  https://github.com/LSatan/SmartRC-CC1101-Driver-Lib

  Pinbezetting:
    GND   -> GND
    VCC   -> 3.3V
    GDO0  -> GPIO 26
    CSN   -> GPIO 5
    SCK   -> GPIO 18
    MOSI  -> GPIO 23
    MISO  -> GPIO 19
    GDO2  -> niet aangesloten
*/

#include <ELECHOUSE_CC1101_SRC_DRV.h>  // wordt mee geïnstalleerd met SmartRC-CC1101-Driver-Lib

// ---- Pin definities ----
#define CC1101_CSN   5
#define CC1101_SCK   18
#define CC1101_MOSI  23
#define CC1101_MISO  19
#define CC1101_GDO0  26
// GDO2 wordt niet gebruikt

// ---- Instellingen ----
#define MHZ 433.92   // pas aan naar de frequentie van je toepassing (vb. 868.35 voor 868MHz)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("CC1101 ontvanger starten...");

  // SPI pinnen instellen (ESP32 heeft geen vaste SPI-pinnen, dus expliciet opgeven)
  ELECHOUSE_cc1101.setSpiPin(CC1101_SCK, CC1101_MISO, CC1101_MOSI, CC1101_CSN);
  ELECHOUSE_cc1101.setGDO(CC1101_GDO0, 0); // GDO2 niet gebruikt -> 0 of zelfde pin als GDO0

  if (ELECHOUSE_cc1101.getCC1101()) {
    Serial.println("CC1101 chip gevonden en verbonden!");
  } else {
    Serial.println("FOUT: CC1101 niet gevonden. Controleer bedrading!");
    while (1) { delay(1000); }
  }

  ELECHOUSE_cc1101.Init();          // initialiseer module
  ELECHOUSE_cc1101.setMHZ(MHZ);     // stel frequentie in
  ELECHOUSE_cc1101.SetRx();         // zet module in ontvangstmodus

  Serial.print("Luisteren op ");
  Serial.print(MHZ);
  Serial.println(" MHz...");
}

void loop() {
  if (ELECHOUSE_cc1101.CheckRxFifo(100)) {  // check of er data binnenkomt (timeout 100ms)
    byte buffer[61] = {0};
    int len = ELECHOUSE_cc1101.ReceiveData(buffer);

    if (len > 0) {
      Serial.print("Ontvangen (");
      Serial.print(len);
      Serial.print(" bytes): ");
      for (int i = 0; i < len; i++) {
        if (buffer[i] < 0x10) Serial.print("0");
        Serial.print(buffer[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      // RSSI en LQI tonen (signaalsterkte / kwaliteit)
      Serial.print("RSSI: ");
      Serial.print(ELECHOUSE_cc1101.getRssi());
      Serial.print(" dBm, LQI: ");
      Serial.println(ELECHOUSE_cc1101.getLqi());
    }
  }
}
