# ESP32 + CC1101 Receiver

Bezig om een **CC1101 RF-module** aan de praat te krijgen met een **ESP32** (CH340 / NodeMCU-32S / WROOM-32 / ESP-WROOM-32), om RF-signalen te ontvangen en te sniffen. Gebruik hiervoor de [SmartRC-CC1101-Driver-Lib](https://github.com/LSatan/SmartRC-CC1101-Driver-Lib).

**Status: lukt nog niet.** Zie hieronder voor mijn concrete probleem — hulp/tips zijn welkom.

## Hardware

- ESP32 development board (CH340 / NodeMCU-32S / WROOM-32 / ESP-WROOM-32)
- CC1101 RF-module (433/868/915 MHz, afhankelijk van versie)
- Jumperwires

## Pinbezetting

| Functie (CC1101) | → ESP32 GPIO |
|---|---|
| GND | GND |
| VCC | **3.3V** |
| GDO0 | GPIO 26 |
| CSN | GPIO 5 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| GDO2 | niet aansluiten |

> ⚠️ De CC1101 werkt op **3.3V**, niet op 5V. Sluit VCC dus aan op de 3.3V-pin van de ESP32.

![Pinbezetting](pinout.png)

## Installatie

1. Installeer de [Arduino IDE](https://www.arduino.cc/en/software) (of gebruik PlatformIO).
2. Installeer ondersteuning voor ESP32-boards via de Boards Manager.
3. Installeer de library **SmartRC-CC1101-Driver-Lib**:
   - Via Arduino IDE: `Sketch → Include Library → Manage Libraries` → zoek op `SmartRC-CC1101-Driver-Lib`
   - Of handmatig via [GitHub](https://github.com/LSatan/SmartRC-CC1101-Driver-Lib) (ZIP downloaden en toevoegen via `Sketch → Include Library → Add .ZIP Library`)
4. Sluit de hardware aan volgens de pinbezetting hierboven.
5. Open `esp32_cc1101_receiver.ino`, pas indien nodig de frequentie (`MHZ`) aan naar de band die je wil ontvangen.
6. Upload de sketch naar je ESP32 en open de Serial Monitor op **115200 baud**.

## Werking

De sketch:
- Initialiseert de CC1101 via SPI met de hierboven gedefinieerde pinnen
- Controleert of de chip correct wordt herkend
- Zet de module in ontvangstmodus (`SetRx()`) op de ingestelde frequentie
- Print ontvangen pakketjes (hex), samen met RSSI (signaalsterkte) en LQI (linkkwaliteit) naar de Serial Monitor

## Mijn probleem — hulp gezocht!

Ik krijg geen enkele communicatie met de CC1101. Heb intussen **3 verschillende CC1101-modules** geprobeerd, allemaal hetzelfde resultaat. Ook al andere libraries getest dan die in deze repo, zonder succes.

**Wat ik in de Serial Monitor krijg:**

```
CC1101 ontvanger starten...
FOUT: CC1101 niet gevonden. Controleer bedrading!
```

Dus de ESP32 boot gewoon normaal op, maar zodra hij de CC1101 probeert te checken, faalt dat meteen.

**Wat ik al heb geprobeerd:**
- 3 verschillende CC1101-modules (zelfde fout bij alle 3)
- Andere library's dan SmartRC-CC1101-Driver-Lib
- Pinbezetting zoals hierboven beschreven

**Wat ik nog niet heb gecheckt:**
- Of elke draad echt goed contact maakt (met multimeter)
- Of de voeding misschien het probleem is (3.3V van de ESP32 zelf is soms te zwak voor de CC1101)
- Of mijn modules misschien een andere pin-volgorde hebben dan de "standaard" layout

Als iemand dit probleem herkent of een goeie tip heeft, hoor ik het graag! Vooral benieuwd of dit een gekend probleem is met goedkope CC1101-modules, of dat ik iets over het hoofd zie in de code/bedrading.

## Feedback welkom

Open gerust een **Issue** als je dit probleem herkent of een suggestie hebt. Ook tips over `setRxBW()`, `setDRate()` of `setModulation()` voor specifieke signalen zijn welkom — daar ben ik ook nog niet aan toegekomen omdat de basisverbinding al niet werkt.

## Licentie

MIT — vrij te gebruiken en aan te passen.
