# IoT-SmartEntry

## 1. Proje Konusu
Bu proje, RFID tabanlı bir IoT kapı kilidi sistemidir. Yetkilendirilmiş RFID kartları kullanılarak kapı kilidi açılabilecek ve giriş-çıkış bilgileri Firebase üzerinden kaydedilip bilgisayara bildirim olarak iletilecektir.

## 2. Proje Kısa Özeti
Akıllı kapı kilidi sistemi, Arduino ve RC522 RFID modülü kullanılarak erişim kontrolü sağlamaktadır. Kullanıcı yetkilendirilmiş bir RFID kart okuttuğunda, sistem Firebase üzerinden kimliği doğrular ve kilidi açar. Ayrıca sistem, giriş-çıkış bilgilerini kaydedip gerçek zamanlı bildirimler gönderebilir. Bu çözüm, evler, ofisler ve güvenlik gerektiren alanlar için güvenli ve düşük maliyetli bir erişim kontrol sistemi sunmaktadır.

## 3. Proje Gereksinimleri
Projeyi çalıştırmak için aşağıdaki donanım ve yazılım bileşenleri gereklidir:

### Donanım:
- Arduino Uno
- RC522 RFID Modülü
- Breadboard
- Jumper Kablolar ve Bağlantı Elemanları

### Yazılım:
- Arduino IDE (Kod yazımı ve yükleme için)
- Firebase Realtime Database (Veri kaydı ve bildirimler için)
- Arduino MFRC522 Kütüphanesi (RC522 modülü için)
- Wi-Fi Modülü (ESP8266/ESP32) veya Ethernet Shield (Firebase ile bağlantı için, tercihe bağlı)

## 4. Projeyi Çalıştırma
Projeyi başlatmak için aşağıdaki adımları takip edebilirsiniz:

### 1. Donanım Bağlantılarını Yapın
- RC522 RFID modülünü Arduino'nun SPI pinlerine bağlayın.
- İhtiyaç duyulan diğer bağlantıları yaparak devreyi tamamlayın.

### 2. Yazılımı Yükleyin
- Arduino IDE'yi açın ve gerekli kütüphaneleri yükleyin:
 
  Arduino IDE > Sketch > Library Manager > "MFRC522" ve "FirebaseESP8266" kütüphanelerini yükleyin
  
- Arduino kodunu yüklemek için aşağıdaki komutu çalıştırın:
 
  Arduino IDE > Tools > Board > "Arduino Uno" seçin ve kodu yükleyin
  
### 3. Firebase Entegrasyonunu Yapın
- Firebase Realtime Database oluşturun ve Arduino kodundaki Firebase bağlantı bilgilerini girin.
- Firebase ile giriş-çıkış verileri kaydedilecek ve bilgisayara bildirimler gönderilecektir.

### 4. Projeyi Çalıştırın
- Arduino'yu bilgisayara bağlayarak seri port üzerinden RFID kart okutmayı test edin.
- Yetkilendirilmiş kartlar ile kapıyı açın, Firebase'de giriş-çıkış bilgilerini kontrol edin.
- Bildirim mekanizmasını test edin.

## 5. Proje Lisans Bilgileri
Bu proje MIT Lisansı altında yayınlanmıştır. Açık kaynak olarak geliştirilmektedir ve ticari veya kişisel projelerde kullanılabilir.

## 6. Proje Anahtar Kelimeleri
- IoT
- RFID
- Akıllı Kapı Kilidi
- Arduino
- Firebase
- Erişim Kontrolü
- Güvenlik Sistemi
- Akıllı Ev Otomasyonu
