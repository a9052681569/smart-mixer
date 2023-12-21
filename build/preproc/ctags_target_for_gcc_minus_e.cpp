# 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino"
# 2 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino" 2
# 3 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino" 2
# 4 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino" 2
# 5 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino" 2
# 6 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino" 2

# 8 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino" 2

/**

 * таксменеджер

 * 

 * цифра указывает возможное количество команд

*/
# 14 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\smart-mixer-v4.ino"
GyverOS<4> OS;

unsigned long lastTime = 0;

void setup() {
 Serial.begin(115200);

 pinMode(2, 0x01);

 startupWifi();

 // настройки крана
 waterFaucet.init(D6);

 // настройка пина датчика потока воды
 pinMode(D5, 0x00);

 mixer.init(makeWarmer, makeColder, data.targetTemp);

 // // настройки операционки
 OS.attach(0, fastTicksTask, 20);
 OS.attach(1, caclFaucetDataTask, 1000);
 OS.attach(2, calcWaterFlowTask, 20);
 OS.attach(3, sendDataTick, 300);

 // Инициализируем ESP-NOW
 initESPNow();
}

void loop() {
 OS.tick(); // вызывать как можно чаще, задачи выполняются здесь
}
