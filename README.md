A project on ESP32-C3, which allows you to control an LED (or other device)
on a schedule of on/off, with a web interface for setting the time.
When you first turn on, an access point appears (ESP32-C3-Config", 12345678),
via the standard WiFiManager library. Next, a web server is started to set the time.
The current time is taken from pool.ntp.org and updated every 10 seconds.
The server and the microcontroller communicate via http get and post requests.
The on and off data is saved via Preferences. 
There is validation of the entered data.

---

Проект на ESP32-C3, позволяющий управлять светодиодом (или другим устройством)
по расписанию включения/выключения, с веб-интерфейсом для настройки времени.
При первом включении появляется точка доступа (ESP32-C3-Config", 12345678),
через стандартную библиотку WiFiManager. Далее запускается веб сервер для настройки времени.
Текущее время берется через pool.ntp.org и обновляется раз в 10 сек.
Сервер и микроконтроллер общаются через http гет и пост запросы.
Данные вкл и выкл сохраняются через Preferences. 
Есть валидация введеных данных.

![photo_2026-03-04_21-00-10](https://github.com/user-attachments/assets/643b8fdc-89b6-4a7f-8e79-2c6eca07a6dc)
