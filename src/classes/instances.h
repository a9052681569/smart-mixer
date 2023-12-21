// #include <GyverOS.h>
#include "temp.h"
#include "faucet.h"
#include "mixer.h"

// термистор на пине А0
// сопротивление резистора 10к
// тепловой коэффициент 3950
TempController tempController(0, 10000, 3950);

/**
 * таксменеджер
 * 
 * цифра указывает возможное количество команд
*/
// GyverOS<3> OS;

/**
 * мотор крана воды
*/
FaucetServo waterFaucet;

Mixer mixer;