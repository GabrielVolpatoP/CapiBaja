#include <iostream>
#include <Tela_Draw.h>
#include <SD_Card.h>
#include <Dual_Nucle.h>
#include <Lora.h>

#define QUEUE_SIZE 10
#define TASK_DELAY 100
#define SERIAL_BAUD_RATE 115200
#define DATA_SEND_INTERVAL 1100

Lora Buffer;
Tela_Draw Tela;
SD_Card Card;
Dual_Nucle Dual;
QueueHandle_t dataQueue;

unsigned long previousMillis = 0;

// Estrutura para armazenar as variáveis
struct SensorData {
  uint8_t buffer_star1, buffer_star2;
  float latitude, longitude;
  uint8_t temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano;
  uint16_t altitude, rpm_motor;
  bool batteryLevel, farol, conct_LAN, low_gas, high_gas;
  uint8_t buffer_end1, buffer_end2;
};

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
    Buffer.sendDataToLora(sensorData);
    Dual.delay(TASK_DELAY / portTICK_PERIOD_MS);
  }
}

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