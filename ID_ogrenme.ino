#include <SPI.h>
#include <RFID.h>

// Bağladığımız pinler
#define SS_PIN 10
#define RST_PIN 9

// RFID modülünü tanıt
RFID rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // Bilgisayara mesaj göndermek için seri haberleşmeyi başlat
  SPI.begin();        // SPI haberleşmesini başlat
  rfid.init();        // RFID modülünü başlat
  Serial.println("Kartı okuyucuya yaklaştır...");
}

void loop() {
  if (rfid.isCard()) { // Kart var mı?
    if (rfid.readCardSerial()) { // Kartın seri numarasını oku
      Serial.print("Kart ID: ");
      for (int i = 0; i < 5; i++) {
        Serial.print(rfid.serNum[i], HEX); // Her byte'ı yaz
        Serial.print(" ");
      }
      Serial.println(); // Yeni satıra geç
      delay(1500); // 1.5 saniye bekle, tekrar okumasın
    }
  }
  rfid.halt(); // Kartı beklemeye al
}
