#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\src\\espnow\\send-data-tick.h"
void sendDataTick() {
	myData.currentTemp = mixer.currentTemp;

	myData.targetTemp = data.targetTemp;

	myData.isWaterFlows = isWaterFlows;

	esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
}