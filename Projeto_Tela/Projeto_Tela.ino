#include <iostream>
#include "Sensor_Data.h"
#include <Tela_Draw.h>
#include <SD_Card.h>
#include <Dual_Nucle.h>
#include <Lora.h>

#define QUEUE_SIZE 10
#define TASK_DELAY 100
#define SERIAL_BAUD_RATE 115200

Lora Buffer;
Tela_Draw Tela;
SD_Card Card;
Dual_Nucle Dual;
QueueHandle_t dataQueue;

// Estrutura para armazenar as variáveis


void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Buffer.setup();
  Tela.setupTela();
  Card.setup();
  dataQueue = Dual.criarFila(QUEUE_SIZE, sizeof(SensorData));
  Dual.criarTarefa(receiverTask, "Receiver", 0);
  Dual.criarTarefa(displayTask, "Display", 1);
}

void receiverTask(void *pvParameters) {
  SensorData sensorData;

  while (true) {
    Buffer.printMensagemTeste(&sensorData);
    Dual.enviarFila(dataQueue, &sensorData);
    writeDataToSDCard(sensorData);
    Buffer.sendDataToLora(&sensorData);
    Dual.delay(TASK_DELAY / portTICK_PERIOD_MS);
  }
}
//SensorData* dados
void writeDataToSDCard(const SensorData &sensorData) {
  Card.criando_Arquivo(SD, "/", 0);
  // Adicione lógica para escrever os dados no SDCard
}

void displayTask(void *pvParameters) {
  SensorData sensorData;

  while (true) {
    if (Dual.receberFila(dataQueue, &sensorData) == pdTRUE) {
      Tela.ExecutarTela();
    }
  }
}

void loop() {
  // O loop fica vazio, já que estamos usando FreeRTOS
}