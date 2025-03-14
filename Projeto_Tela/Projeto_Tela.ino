#include <iostream>
#include "Sensor_Data.h"
#include <Tela_Draw.h>
#include <SD_Card.h>
#include <Dual_Nucle.h>
#include <Lora.h>

#define QUEUE_SIZE 10
#define TASK_DELAY 100
#define SERIAL_BAUD_RATE 115200

Lora lora;
Tela_Draw tela;
SD_Card card;
Dual_Nucle dual;
QueueHandle_t dataQueue;

// Estrutura para armazenar as variáveis


void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  lora.setup();
  tela.setup();
  card.setup();
  dataQueue = dual.criarFila(QUEUE_SIZE, sizeof(SensorData));
  dual.criarTarefa(receiverTask, "Receiver", 0);
  dual.criarTarefa(displayTask, "Display", 1);
}

void receiverTask(void *pvParameters) {
  SensorData sensorData;

  while (true) {
    lora.printMensagemTeste(&sensorData);
    dual.enviarFila(dataQueue, &sensorData);
    writeDataToSDCard(sensorData);
    lora.sendDataToLora(&sensorData);
    dual.delay(TASK_DELAY / portTICK_PERIOD_MS);
  }
}
//SensorData* dados
void writeDataToSDCard(const SensorData &sensorData) {
  card.criando_Arquivo(SD, "/", 0);
  // Adicione lógica para escrever os dados no SDCard
}

void displayTask(void *pvParameters) {
  SensorData sensorData;

  while (true) {
    if (dual.receberFila(dataQueue, &sensorData) == pdTRUE) {
      tela.ExecutarTela();
    }
  }
}

void loop() {
  // O loop fica vazio, já que estamos usando FreeRTOS
}