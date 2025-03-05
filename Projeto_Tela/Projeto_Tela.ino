#include <iostream>          // Dados Binarios
#include <HardwareSerial.h>  // Comunicação Lora
HardwareSerial lora(1);      // Usa UART1 do ESP32

// <tela>
#include <Tela_Draw.h>
Tela_Draw Tela;

// <SdCard>
#include <SD_Card.h>
SD_Card Card;

// <Lora>
#define pinRx 7  // Pino Lora
#define pinTx 8  // Pino Lora
unsigned long previousMillis = 0;

// <Duplo Nucleo>
#include <Dual_Nucle.h>
Dual_Nucle Dual;

// Fila para passar dados entre as tarefas /(?)
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

  // Inicializando o display
  Tela.setupTela();  // Inicializa o display

  // Inicializando o SD Card
  Card.setup();

  // Criando a fila
  dataQueue = Dual.criarFila(10, sizeof(SensorData));

  // Criando as tarefas
  Dual.criarTarefa(receiverTask, "Receiver", 2048, NULL, 1, NULL, 0);  // Núcleo 0
  Dual.criarTarefa(displayTask, "Display", 2048, NULL, 1, NULL, 1);    // Núcleo 1
}
// Tarefa para receber dados
void receiverTask(void *pvParameters) {
  while (true) {
    SensorData sensorData;

    // Simulando a recepção de dados
    sensorData.temperatura_motor = random(9, 55);  // Valore Aleatorios para variavel
    sensorData.rpm_motor = random(9, 55);          // Valore Aleatorios para variavel
    sensorData.velocidade = random(5, 45);         // Valore Aleatorios para variavel
    sensorData.odometro = random(300, 3000);       // Valore Aleatorios para variavel

    // Enviar dados para a fila
    Dual.enviarFila(dataQueue, &sensorData);

    // ____ SDCard _____
    Card.criando_Arquivo(SD, "/", 0);

    String data = "OMELHORBAJA, " + String(sensorData.low_gas) + ", " + String(sensorData.high_gas) + ", " + String(sensorData.farol) + ", " + String(sensorData.batteryLevel) + ", " + String(sensorData.conct_LAN) + ", " + String(sensorData.temperatura_cvt) + ", " + String(sensorData.velocidade) + ", " + String(sensorData.odometro);
    if (millis() - previousMillis >= 1100) {
      previousMillis = millis();
      lora.print(data);
    }
    Dual.delay(100 / portTICK_PERIOD_MS);  // Espera 1 segundo
  }
}

// Tarefa para exibir dados
void displayTask(void *pvParameters) {
  while (true) {
    SensorData sensorData;
    if (Dual.receberFila(dataQueue, &sensorData) == pdTRUE) {
      // Construção da tela

      // ___ Tela ___
      Tela.ExecutarTela();
    }
  }
}


void loop() {
  // O loop fica vazio, já que estamos usando FreeRTOS
}
