#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\include.h"
// импорты данных, должны идти до импортов использующих их файлов
#include "./src/data/data.h"

#include "./src/ui/ui-data.h"

// инициированные инстансы используемых классов
#include "./src/classes/instances.h"

#include "./src/espnow/actions.h"
#include "./src/espnow/init.h"
#include "./src/espnow/send-data-tick.h"

// функции задач
#include "./src/tasks/tasks.h"

// импорт настройки вайфай. Должен идти в конце, чтобы у него был доступ ко всем используемым данным
#include "./src/wifi/wifi-startup.h"