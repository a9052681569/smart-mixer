#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\src\\espnow\\init.h"
void initESPNow() {
	if (esp_now_init() == 0) {
		Serial.println("Успешно инициализировали");
	} else {
		Serial.println("Ошибка инициализации ESP-NOW");
		return;
	}
	
	// Роль платы в ESP-NOW
	esp_now_set_self_role(ESP_NOW_ROLE_COMBO);  
	esp_now_register_recv_cb(OnDataRecv);
	esp_now_register_send_cb(OnDataSent);                                   // Получаем сообщение об отправке
	esp_now_add_peer(controllerMac, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}