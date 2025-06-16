#include <SPI.h>
#include <RFID.h>

#define RFID_SS_PIN 10
#define RFID_RST_PIN 9
#define LED_GREEN 3
#define LED_RED   2
#define BUZZER_PIN 7

RFID rfid(RFID_SS_PIN, RFID_RST_PIN);

// Birden fazla yetkili kart UID'si (buraya ekle)
byte kartlar[][5] = {
  {0xC1, 0x2C, 0x5F, 0x1D, 0xAF},    // Kart 1 (senin kartın)
  {0xF4, 0xA1, 0x0E, 0x04, 0x5F}     // Kart 2 (örnek)
};
const int kart_sayisi = sizeof(kartlar) / sizeof(kartlar[0]);

// UID'yi stringe çeviren fonksiyon
String uidToString(byte *uid, byte len) {
  String s = "";
  for (byte i = 0; i < len; i++) {
    if (uid[i] < 0x10) s += "0";
    s += String(uid[i], HEX);
  }
  s.toUpperCase();
  return s;
}

// Melodi ve Türk Marşı fonksiyonları aynı kalabilir

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784

void playMelodiliUyari() {
  int melody[] = {
    NOTE_E5, NOTE_E5, 0, NOTE_E5,
    0, NOTE_C5, NOTE_E5, 0,
    NOTE_G5, 0, 0, NOTE_G4
  };
  int durations[] = {
    8, 8, 8, 8,
    8, 8, 8, 8,
    4, 8, 8, 4
  };
  for (int i = 0; i < 12; i++) {
    int noteDuration = 1000 / durations[i];
    if (melody[i] != 0) {
      tone(BUZZER_PIN, melody[i], noteDuration);
    }
    delay(noteDuration * 1.3);
    noTone(BUZZER_PIN);
  }
}

void playTurkMars() {
  int melody[] = {
    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4
  };
  int durations[] = {
    8, 8, 8, 8, 8, 8, 8, 8,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2
  };
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
    int duration = 1000 / durations[i];
    tone(BUZZER_PIN, melody[i], duration);
    delay(duration * 1.3);
    noTone(BUZZER_PIN);
  }
}

// UID dizilerini karşılaştıran fonksiyon
bool isAuthorized(byte *uid) {
  for (int k = 0; k < kart_sayisi; k++) {
    bool esit = true;
    for (int j = 0; j < 5; j++) {
      if (kartlar[k][j] != uid[j]) {
        esit = false;
        break;
      }
    }
    if (esit) return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("=== RFID Okuyucu Başlatıldı ===");
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      String uidStr = uidToString(rfid.serNum, 5);
      bool gecerliKart = isAuthorized(rfid.serNum);

      if (gecerliKart) {
        Serial.println("{\"kartID\":\"" + uidStr + "\",\"durum\":\"yetkili\"}");
        digitalWrite(LED_GREEN, HIGH);
        playMelodiliUyari();
        digitalWrite(LED_GREEN, LOW);
      } else {
        Serial.println("{\"kartID\":\"" + uidStr + "\",\"durum\":\"reddedildi\"}");
        digitalWrite(LED_RED, HIGH);
        playTurkMars();
        digitalWrite(LED_RED, LOW);
      }

      rfid.halt();
    }
  }
}