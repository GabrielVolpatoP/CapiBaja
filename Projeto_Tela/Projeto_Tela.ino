#include <iostream>          // Dados Binarios
#include <Tela_Draw.h>       // <tela>
#include <SD_Card.h>         // <SdCard>
#include <Dual_Nucle.h>      // <Duplo Nucleo>
#include <HardwareSerial.h>  // Comunicação Lora

#define pinRx 7           // Pino Lora
#define pinTx 8           // Pino Lora
Tela_Draw Tela;           // Classe <Tela>
SD_Card Card;             // Classe <Card>
Dual_Nucle Dual;          // Classe <Dual>
HardwareSerial lora(1);   // Usa UART1 do ESP32
QueueHandle_t dataQueue;  // Fila para passar dados entre as tarefas

unsigned long previousMillis = 0;

struct SensorData {  // Estrutura para os dados agregados
  float latitude, longitude;
  uint8_t temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano;
  uint16_t altitude, rpm_motor;
  bool batteryLevel, farol, conct_LAN, low_gas, high_gas;
};

void setup() {
  Serial.begin(115200);                          // Serial deplay
  lora.begin(115200, SERIAL_8N1, pinRx, pinTx);  // Inicializa Lora
  Tela.setupTela();                              // Inicializa o display
  Card.setup();                                  // Inicializando o SDCard

  dataQueue = Dual.criarFila(10, sizeof(SensorData));  // Criando a fila <Dual>
  Dual.criarTarefa(receiverTask, "Receiver", 0);       // Núcleo 0
  Dual.criarTarefa(displayTask, "Display", 1);         // Núcleo 1
}

void receiverTask(void *pvParameters) {  // Tarefa para receber dados
  while (true) {
    SensorData sensorData;

    // Simulando a recepção de dados
    sensorData.temperatura_motor = random(9, 55);  // Valore Aleatorios para variavel
    sensorData.rpm_motor = random(9, 55);          // Valore Aleatorios para variavel
    sensorData.velocidade = random(5, 45);         // Valore Aleatorios para variavel
    sensorData.odometro = random(300, 3000);       // Valore Aleatorios para variavel

    Dual.enviarFila(dataQueue, &sensorData);  // Enviar dados para a fila

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

      // ___ Tela ___
      Tela.ExecutarTela();  // Construção da tela
    }
  }
}

void loop() {
  // O loop fica vazio, já que estamos usando FreeRTOS
}
