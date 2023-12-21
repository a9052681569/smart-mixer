#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\src\\data\\data.h"
#include <GyverPortal.h>
#include <EEManager.h>

bool isWaterFlows = false;

String wifiSignal = "pizda";

uint8_t mixerMac[] = {0xC8, 0xC9, 0xA3, 0x33, 0xC5, 0x9B};
uint8_t testMixerMac[] = {0xDC, 0x4F, 0x22, 0x7F, 0x73, 0xCA};
uint8_t controllerMac[] = {0xC8, 0xC9, 0xA3, 0x33, 0xB6, 0xB1};

// структуры для отправки данных
typedef struct struct_message {
    int targetTemp = 0;
    int currentTemp = 0;
	bool sending = true;
	bool isWaterFlows = false;
} struct_message;


// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message theirData;   

/**
 * данные, которые мы хотим хранить между запусками
*/
struct EEPROMData {
  char ssid[20] = "";
  char pass[20] = "";
  int targetTemp = 37;
  bool isManual = false;
};

EEPROMData data;

EEManager eemem(data);
