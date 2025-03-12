# Akıllı Kapı Kilidi - Öneri Raporu

## 1. Proje Konusu

Bu proje, RFID tabanlı bir IoT kapı kilidi sistemidir. Kullanıcılar, yetkilendirilmiş RFID kartları ile kapı kilidini açabilecektir. Arduino mikrodenetleyicisi, **RC522 RFID modülü** kullanarak güvenli bir erişim sistemi oluşturulması hedeflenmektedir. **Kilidi fiziksel olarak açmak yerine, giriş-çıkış bilgileri Firebase üzerinden kaydedilerek bilgisayara bildirim gönderilecektir.**

## 2. Proje Hedefleri

- Kullanıcı dostu ve güvenli bir erişim kontrol sistemi tasarlamak.
- **RC522 RFID modülü ile kart tanıma ve doğrulama mekanizması kurmak**.
- **Arduino kullanarak RFID okutma işlemini Firebase ile kaydetmek ve bilgisayara bildirim göndermek**.
- Geliştirilebilir ve kolay entegre edilebilir bir sistem oluşturmak.
- **İlerleyen süreçte ek özellikler ve entegrasyonlar eklenebilir.**

## 3. Tahmini Zaman Çizelgesi

| Görev                                         | Tahmini Süre               |
| --------------------------------------------- | -------------------------- |
| Donanım Bağlantılarını Yapılandırma           | 1 Hafta                    |
| RFID Kart Tanıtma ve Arduino Programlama      | 2 Hafta                    |
| Firebase Entegrasyonu ve Bildirim Sistemi     | 2 Hafta                    |
| Test ve Optimizasyon                          | 1 Hafta                    |
| **Eklemeler ve Geliştirmeler (İleri Seviye)** | Süreç Tamamlandıktan Sonra |

## 4. Kaynak Planlaması

| Görev                      |    Sorumlu      |
| -------------------------- | --------------- |
| Donanım Bağlantıları       | Adile Akkılıç   |
| Arduino Kodlama            | Dilek Yılmaz    |
| Firebase Entegrasyonu      | Sude Telli      |
| Test ve Raporlama          | Şevval Nur Öksüz|

**Gereken Donanımlar ve Tahmini Maliyet:**

- **Arduino Uno** → 250 TL
- **RC522 RFID Modülü** → 150 TL
- **Breadboard** → 50 TL
- **Jumper Kablolar ve Bağlantı Elemanları** → 100 TL
- **Toplam:** 550 TL

## 5. Risk Analizi

| Risk                          | Çözüm                                                         |
| ----------------------------- | ------------------------------------------------------------- |
| RFID kart doğrulama hatası    | **RC522 kütüphanelerinin doğru kullanımı sağlanacak**         |
| Arduino Bağlantı Sorunları    | **Kablolama ve pin bağlantıları dikkatlice kontrol edilecek** |
| Bağlantı kesintileri          | **Firebase bağlantısı optimize edilecek**                     |
| Bilgisayar bildirim sorunu    | **Bildirim mekanizması test edilerek optimize edilecek**      |
| **Ek Özelliklerin Eklenmesi** | **Sistem tamamlandıktan sonra modüler geliştirme yapılacak**  |

## 6. Ticari Potansiyel

Bu proje, **akıllı evler, ofisler, oteller ve güvenlik gerektiren alanlar** için düşük maliyetli ve uygulanabilir bir **erişim kontrol sistemi** olarak değerlendirilebilir. **RC522 RFID modülü ile kullanıcı tanıma özelliği**, işletmelerin güvenliğini artırmada önemli bir avantaj sunar. **Fiziksel kilit yerine Firebase bildirim sistemi ile çalışan model**, veri kaydı ve giriş-çıkış analizleri açısından modern bir çözüm sunar. Özelleştirilebilir yapısıyla geniş bir kullanım alanına sahiptir.

**İleri aşamalarda eklemeler ve geliştirmeler için sistemin modüler yapıda tasarlanması planlanmaktadır.**

