// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef Lora_H
#define Lora_H

#include <HardwareSerial.h>
#include "Sensor_Data.h"

// ------------------------------------------------------------

class Lora {
public:
	
	void setup();
	void analiseMensagem(SensorData* dados);
	void printMensagemTeste(SensorData* dados);	
	void sendDataToLora(SensorData* dados);

};
	
#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.

