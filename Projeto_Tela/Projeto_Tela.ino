#include <Sensor_Data.h>
#include <Tela_Draw.h>
#include <SD_Card.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#define SERIAL_BAUD_RATE 9600
#define TASK_DELAY 100

Tela_Draw tela;
SensorData dataStruct;
SD_Card card;

char dados[532];
QueueHandle_t dataQueue;  // Fila para passar dados entre as tarefas

// Tarefa para receber dados
void receiverTask(void *pvParameters) {
  while (true) {
    // Simulando a recepção de dados
    randomicString(dados);
    //char *dataString = dataFunction.sensorDataToString(&dataStruct);
    card.incrementandoArquivo("/Teste/teste.csv", dados);  // Incrementa dados no arquivo
    card.lendoArquivo("/Teste/teste.csv");                 // Le a informação do Arquivo renomeado

    xQueueSend(dataQueue, &dataStruct, portMAX_DELAY);  // Enviar dados para a fila
    vTaskDelay(TASK_DELAY / portTICK_PERIOD_MS);        // Espera 1 segundo
  }
}

// Tarefa para exibir dados
void displayTask(void *pvParameters) {
  while (true) {
    if (xQueueReceive(dataQueue, &dataStruct, portMAX_DELAY) == pdTRUE) {
      tela.atulizacaoTela(&dataStruct);
      tela.desenharTela();
    }
  }
}

void randomicString(char *buffer) {

  dataStruct.buffer_star1 = 123;
  dataStruct.buffer_star2 = 123;
  dataStruct.latitude = static_cast<float>(std::rand()) / RAND_MAX * 180.0f - 90.0f;
  dataStruct.longitude = static_cast<float>(std::rand()) / RAND_MAX * 360.0f - 180.0f;
  dataStruct.temperatura_motor = std::rand() % 60;
  dataStruct.temperatura_cvt = std::rand() % 60;
  dataStruct.velocidade = std::rand() % 60;
  dataStruct.odometro = std::rand() % 256;
  dataStruct.hora = std::rand() % 24;
  dataStruct.minuto = std::rand() % 60;
  dataStruct.mes = std::rand() % 12 + 1;
  dataStruct.ano = std::rand() % 100;  // Assumindo um valor de 0 a 99 para o ano
  dataStruct.altitude = std::rand() % 65536;
  dataStruct.rpm_motor = std::rand() % 65536;
  dataStruct.batteryLevel = std::rand() % 2;
  dataStruct.farol = std::rand() % 2;
  dataStruct.conct_LAN = std::rand() % 2;
  dataStruct.low_gas = std::rand() % 2;
  dataStruct.high_gas = std::rand() % 2;
  dataStruct.buffer_end1 = 123;
  dataStruct.buffer_end2 = 123;

  sprintf(buffer,
          "%u,%u,%.6f,%.6f,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d,%d,%u,%u",
          dataStruct.buffer_star1, dataStruct.buffer_star2, dataStruct.latitude, dataStruct.longitude,
          dataStruct.temperatura_motor, dataStruct.temperatura_cvt, dataStruct.velocidade, dataStruct.odometro,
          dataStruct.hora, dataStruct.minuto, dataStruct.mes, dataStruct.ano, dataStruct.altitude, dataStruct.rpm_motor,
          dataStruct.batteryLevel, dataStruct.farol, dataStruct.conct_LAN, dataStruct.low_gas, dataStruct.high_gas,
          dataStruct.buffer_end1, dataStruct.buffer_end2);
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);   // inicializa a comunicação serial
  tela.setup();                     // Inicializando o display
  card.setup();                     // Inicializando o SD Card
  card.criandoDiretorio("/Teste");  // Cria uma pasta no SD
  card.criandoArquivo("/Teste/teste.csv", "buffer_star1, buffer_star2, latitude, longitude, temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano, altitude, rpm_motor, batteryLevel, farol, conct_LAN, low_gas, high_gas, buffer_end1, buffer_end2");
  card.lendoArquivo("/Teste/teste.csv");

  dataQueue = xQueueCreate(10, sizeof(SensorData));  // Criando a fila
  // Criando as tarefas
  xTaskCreatePinnedToCore(receiverTask, "Receiver", 2048, NULL, 1, NULL, 0);  // Núcleo 0
  xTaskCreatePinnedToCore(displayTask, "Display", 2048, NULL, 1, NULL, 1);    // Núcleo 1
}

void loop() { /* O loop fica vazio, já que estamos usando FreeRTOS*/
}