#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\src\\espnow\\actions.h"
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
	Serial.print("\r\nСтатус Отправки Последнего Пакета: ");
	if (sendStatus == 0){
		Serial.println("Сообщение доставлено");
	} else {
		Serial.println("Сообщение НЕ доставлено");
	}
}

void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  	char macStr[18];
	Serial.print("Packet received from: ");
	snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
			mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
	Serial.println(macStr);
  	memcpy(&theirData, incomingData, sizeof(theirData));

  // Update the structures with the new incoming data
	if (theirData.sending) {
		myData.targetTemp = theirData.targetTemp;
		data.targetTemp = theirData.targetTemp;
	}
	// Serial.printf("currentTemp: %d \n", slaveData.currentTemp);
	// Serial.printf("targerTemp: %d \n", slaveData.targerTemp);
	// Serial.println();
}