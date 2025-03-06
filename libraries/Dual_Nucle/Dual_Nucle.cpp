// Implementação 
// Define como as funções trabalham e quais operações realizam.
#include "Dual_Nucle.h" // Importa o cabeçalho para garantir que as declarações das funções sejam reconhecidas.

// ------------------------------------------------------------


// Criando as tarefas <Dual>
void Dual_Nucle::criarTarefa(TaskFunction_t receiverTask, const char * receiver, BaseType_t nucleo){
	xTaskCreatePinnedToCore(receiverTask, receiver,  2048, NULL, 1, NULL, nucleo); 
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
