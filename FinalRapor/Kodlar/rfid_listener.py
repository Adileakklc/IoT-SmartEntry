import pyttsx3
import serial, json, requests, time, threading
from plyer import notification
import tkinter as tk
from tkinter.scrolledtext import ScrolledText

# === AYARLAR ===
PORT   = "COM11"
BAUD   = 9600
FB_URL = "https://kart-269c1-default-rtdb.firebaseio.com/girisler.json"
# ===============

# --- Tema ayarları ---
themes = {
    "Light": {
        "bg": "#f2f2f2",
        "fg": "#000000",
        "console_bg": "#ffffff",
        "console_fg": "#000000",
        "status_bg": "#e0e0e0",
        "status_fg": "green",
        "button_bg": "#d35400",
        "button_fg": "#ffffff",
        "clock_fg": "#333333"
    },
    "Dark": {
        "bg": "#2c3e50",
        "fg": "#ecf0f1",
        "console_bg": "#34495e",
        "console_fg": "#ecf0f1",
        "status_bg": "#1abc9c",
        "status_fg": "#000000",
        "button_bg": "#e74c3c",
        "button_fg": "#ffffff",
        "clock_fg": "#bdc3c7"
    }
}
current_theme = "Dark"

# --- TKİNTER GUI ---
root = tk.Tk()
root.title("RFID Kart Giriş Sistemi")
root.geometry("520x420")
root.resizable(False, False)

# Tema uygula fonksiyonu
def apply_theme(theme_name):
    theme = themes[theme_name]
    root.configure(bg=theme["bg"])
    label.config(bg=theme["bg"], fg=theme["fg"])
    status_label.config(bg=theme["status_bg"], fg=theme["status_fg"])
    console_area.config(bg=theme["console_bg"], fg=theme["console_fg"])
    clear_btn.config(bg=theme["button_bg"], fg=theme["button_fg"], activebackground=theme["button_bg"])
    clock_label.config(bg=theme["bg"], fg=theme["clock_fg"])
    theme_menu.config(bg=theme["bg"], fg=theme["fg"], highlightbackground=theme["bg"])

# Tema değiştirme menüsü
def change_theme(choice):
    global current_theme
    current_theme = choice
    apply_theme(choice)

theme_var = tk.StringVar(value=current_theme)
theme_menu = tk.OptionMenu(root, theme_var, *themes.keys(), command=change_theme)
theme_menu.pack(anchor="ne", padx=10, pady=5)

# Başlık
label = tk.Label(root, text=" RFID Kart Giriş Sistemi", font=("Helvetica", 18, "bold"))
label.pack(pady=10)

# Durum etiketi
status_label = tk.Label(root, text="Hazır", font=("Helvetica", 14), width=30)
status_label.pack(pady=5)

# Console alanı
console_area = ScrolledText(root, width=62, height=11, font=("Consolas", 10), bd=0, relief="flat", wrap="word")
console_area.pack(pady=10, padx=8)

# Temizle butonu
def clear_console():
    console_area.delete(1.0, tk.END)

clear_btn = tk.Button(root, text="Temizle", command=clear_console, relief="flat", bd=0, font=("Arial", 10, "bold"))
clear_btn.pack(pady=5)

# Saat gösterimi
clock_label = tk.Label(root, text="", font=("Arial", 10))
clock_label.pack(side="bottom", pady=5)

def update_clock():
    current_time = time.strftime("%H:%M:%S %d-%m-%Y")
    clock_label.config(text=current_time)
    root.after(1000, update_clock)

update_clock()

# Konsola log yazma
def log_console(text):
    console_area.config(state="normal")
    console_area.insert(tk.END, text + "\n")
    console_area.see(tk.END)
    console_area.config(state="disabled")

# Firebase gönderim
def push_firebase(payload):
    try:
        r = requests.post(FB_URL, json=payload, timeout=5)
        r.raise_for_status()
    except requests.RequestException as e:
        log_console(f"[Firebase HATA] {e}")

# Bildirim
def show_notification(title, message):
    notification.notify(
        title=title,
        message=message,
        timeout=3,
        toast=True
    )

# Sesli okuma
def speak(text):
    engine = pyttsx3.init()
    engine.say(text)
    engine.runAndWait()

# Seri port okuma
def read_from_serial():
    def set_status(ok, msg="Hazır"):
        if ok:
            status_label.config(text="🟢 Bağlı - " + msg)
        else:
            status_label.config(text="🔴 Bağlantı Yok - " + msg)
    try:
        with serial.Serial(PORT, BAUD, timeout=1) as ser:
            set_status(True, "Kart bekleniyor")
            while True:
                line = ser.readline().decode(errors="ignore").strip()
                if not line or len(line) < 5:
                    time.sleep(0.05)
                    continue
                try:
                    data = json.loads(line)
                    push_firebase(data)
                    show_notification("RFID Kapı", f"{data['kartID']} ➜ {data['durum']}")
                    log_console(f"Gönderildi: {data['kartID']} ➜ {data['durum']}")
                    if data["durum"].lower() == "yetkili":
                        speak("Hoş geldiniz, geçiş yetkiniz onaylandı!")
                    else:
                        speak("Üzgünüz, bu kartla giriş izni yok.")
                except json.JSONDecodeError:
                    continue
    except Exception as e:
        set_status(False, f"[Bağlantı Hatası] {e}")
        log_console(f"[Bağlantı Hatası] {e}")

# Temayı başta uygula
apply_theme(current_theme)

# Konsol pasif başlasın
console_area.config(state="disabled")

# Seri okuma thread’i başlatılır
threading.Thread(target=read_from_serial, daemon=True).start()

root.mainloop()
