#include <iostream>
#include <Tela_Draw.h>
#include <SD_Card.h>
#include <Dual_Nucle.h>
#include <HardwareSerial.h>

#define PIN_RX 17 // Lora
#define PIN_TX 16 // Lora
#define QUEUE_SIZE 10
#define TASK_DELAY 100
#define LORA_BAUD_RATE 115200
#define SERIAL_BAUD_RATE 115200
#define DATA_SEND_INTERVAL 1100
#define SD_SCK   14  // Clock
#define SD_MISO  12  // Entrada de dados
#define SD_MOSI  13  // Saída de dados
#define SD_CS    27  // Chip Select (ajuste conforme necessário)

Tela_Draw Tela;
SD_Card Card;
Dual_Nucle Dual;
HardwareSerial lora(1);
QueueHandle_t dataQueue;

unsigned long previousMillis = 0;

struct SensorData {
  float latitude, longitude;
  uint8_t temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano;
  uint16_t altitude, rpm_motor;
  bool batteryLevel, farol, conct_LAN, low_gas, high_gas;
};

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  lora.begin(LORA_BAUD_RATE, SERIAL_8N1, PIN_RX, PIN_TX);
  Tela.setupTela();
  Card.setup();
  dataQueue = Dual.criarFila(QUEUE_SIZE, sizeof(SensorData));
  Dual.criarTarefa(receiverTask, "Receiver", 0);
  Dual.criarTarefa(displayTask, "Display", 1);
}

void receiverTask(void *pvParameters) {
  SensorData sensorData;

  while (true) {
    collectSensorData(sensorData);
    Dual.enviarFila(dataQueue, &sensorData);
    writeDataToSDCard(sensorData);
    sendDataToLora(sensorData);
    Dual.delay(TASK_DELAY / portTICK_PERIOD_MS);
  }
}

void collectSensorData(SensorData &sensorData) {
  sensorData.temperatura_motor = random(9, 55);
  sensorData.temperatura_cvt = random(9, 55);
  sensorData.velocidade = random(5, 45);
  sensorData.odometro = random(300, 3000);
  sensorData.rpm_motor = random(500, 9000);
}

void writeDataToSDCard(const SensorData &sensorData) {
  Card.criando_Arquivo(SD, "/", 0);
  // Adicione lógica para escrever os dados no SDCard
}

void sendDataToLora(const SensorData &sensorData) {
  if (millis() - previousMillis >= DATA_SEND_INTERVAL) {
    previousMillis = millis();
    char data[128];
    snprintf(data, sizeof(data), "OMELHORBAJA, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
             sensorData.low_gas, sensorData.high_gas, sensorData.farol, sensorData.batteryLevel,
             sensorData.temperatura_motor, sensorData.rpm_motor, sensorData.velocidade, sensorData.odometro,
             sensorData.hora, sensorData.minuto, sensorData.mes, sensorData.ano);
    lora.print(data);
  }
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
