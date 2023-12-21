void sendDataTick() {
	myData.currentTemp = mixer.currentTemp;

	myData.targetTemp = data.targetTemp;

	myData.isWaterFlows = isWaterFlows;

	esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
}