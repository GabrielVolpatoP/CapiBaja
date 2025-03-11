// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef Lora_H
#define Lora_H

#include <HardwareSerial.h>

// ------------------------------------------------------------

class Lora {
public:
	
	void setup();
	void analiseMensagem(struct &sensorData);
	void checagemBuffer();
	void printMensagemTeste(struct &sensorData);	
	void sendDataToLora(struct &sensorData);

};
	
#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.

