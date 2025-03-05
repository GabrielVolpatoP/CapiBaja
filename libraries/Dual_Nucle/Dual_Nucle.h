// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef Dual_Nucle_H
#define Dual_Nucle_H

#include <freertos/FreeRTOS.h>  // Dual Tela
#include <freertos/task.h>      // Dual Tela
#include <freertos/queue.h>     // Dual Tela

// ------------------------------------------------------------

class Dual_Nucle {
public:
	
	void criarTarefa(TaskFunction_t receiverTask, const char * receiver, UBaseType_t sizePilha, void * ponteiro, UBaseType_t propriedade, TaskHandle_t handleTask, BaseType_t nucleo);
	QueueHandle_t criarFila(int sizeFila, int sizeStruct);
	void delay(int numerador);
	void enviarFila(QueueHandle_t dadosFila, void * ponteiro);
	bool receberFila(QueueHandle_t handleFila, void * ponteiro);	
	
};
	
#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.

