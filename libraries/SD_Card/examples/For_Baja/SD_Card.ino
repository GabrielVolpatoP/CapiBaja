// Dois nucleos
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include <iostream>  // Dados Binarios

#include <HardwareSerial.h>
HardwareSerial lora(1); // Usa UART1 do ESP32

// SD Card -
#include <SD_Card.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include "sd_defines.h"
SD_Card Card;


//Variaveis para Lora
//Pinos Lora
#define pinRx 7
#define pinTx 8
unsigned long previousMillis = 0;

String msg;

// Definições do display (exemplo para I2C)

// Fila para passar dados entre as tarefas
QueueHandle_t dataQueue;

// Estrutura para os dados agregados
struct SensorData {
  float latitude, longitude;
  uint8_t temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano;
  uint16_t altitude, rpm_motor;
  bool batteryLevel, farol, conct_LAN, low_gas, high_gas;
};

void setup() {
  Serial.begin(115200);
  lora.begin(115200, SERIAL_8N1, pinRx, pinTx);

  Card.setup();

  // Criando a fila
  dataQueue = xQueueCreate(10, sizeof(SensorData));

  // Criando as tarefas
  xTaskCreatePinnedToCore(receiverTask, "Receiver", 2048, NULL, 1, NULL, 0);  // Núcleo 0
  xTaskCreatePinnedToCore(displayTask, "Display", 2048, NULL, 1, NULL, 1);    // Núcleo 1
}



// Variáveis para armazenar valores anteriores
// SensorData previousData = { 0, 0, 0 };

// Tarefa para receber dados
void receiverTask(void *pvParameters) {
  while (true) {
    SensorData sensorData;

    // Simulando a recepção de dados
    sensorData.temperatura_motor = random(9, 55);         // Valore Aleatorios para variavel
    sensorData.rpm_motor = random(9, 55);                 // Valore Aleatorios para variavel
    sensorData.velocidade = random(5, 45);                // Valore Aleatorios para variavel
    sensorData.odometro = random(300, 3000);              // Valore Aleatorios para variavel
    //sensorData.batteryLevel = random(0, 100);           // Valore Aleatorios para variavel

    // Enviar dados para a fila
    xQueueSend(dataQueue, &sensorData, portMAX_DELAY);

    // _______________ SDCard ______________________________

    Card.armazenamento_Geral(SD);

    // _______________ SDCard ______________________________

    String data = "OMELHORBAJA, " + String(sensorData.low_gas) + ", " + String(sensorData.high_gas) + ", " + String(sensorData.farol) + ", " + String(sensorData.batteryLevel) + ", " + String(sensorData.conct_LAN) + ", " + String(sensorData.temperatura_cvt) + ", " + String(sensorData.velocidade) + ", " + String(sensorData.odometro);
    if(millis() - previousMillis >= 1100){
      previousMillis = millis();
      lora.print(data);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);                 // Espera 1 segundo
  }
}

// Tarefa para exibir dados
void displayTask(void *pvParameters) {
  while (true) {
    SensorData sensorData;
    if (xQueueReceive(dataQueue, &sensorData, portMAX_DELAY) == pdTRUE) {
      // Construção da tela      
    }
  }
}


void loop() {
  // O loop fica vazio, já que estamos usando FreeRTOS
}