// Implementação 
// Define como as funções trabalham e quais operações realizam.
#include "Dual_Nucle.h" // Importa o cabeçalho para garantir que as declarações das funções sejam reconhecidas.

// ------------------------------------------------------------

void Dual_Nucle::criarTarefa(TaskFunction_t receiverTask, const char * receiver, UBaseType_t sizePilha, void * ponteiro, UBaseType_t propriedade, tskTaskControlBlock* handleTask, BaseType_t nucleo){
	xTaskCreatePinnedToCore(receiverTask, receiver, sizePilha, ponteiro, propriedade, handleTask, nucleo); 
}

// ------------------------------------------------------------

QueueHandle_t Dual_Nucle::criarFila(int sizeFila, int sizeStruct){
	xQueueCreate(sizeFila, sizeof(sizeStruct));
}

// ------------------------------------------------------------

void Dual_Nucle::delay(int numerador){
	vTaskDelay(numerador / portTICK_PERIOD_MS);
}

// ------------------------------------------------------------

void Dual_Nucle::enviarFila(QueueHandle_t dadosFila, void * ponteiro){
	xQueueSend(dadosFila, &ponteiro , portMAX_DELAY); //&
}

// ------------------------------------------------------------

bool Dual_Nucle::receberFila(QueueHandle_t handleFila, void * ponteiro){
	xQueueReceive(handleFila, &ponteiro, portMAX_DELAY);
}
