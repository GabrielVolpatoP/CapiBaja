#include <Sensor_Data.h>
#include <Tela_Draw.h>
#include <SD_Card.h>

#define SERIAL_BAUD_RATE 9600
#define TASK_DELAY 100

Tela_Draw tela;
SensorData data;
SD_Card card;

char dados[600];

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);  // inicializa a comunicação serial
  tela.setup();                    // Inicializando o display
  //tela.desenharTela();
  card.setup();  // Inicializando o SD Card
  //card.criandoDiretorio("/Teste");  // Cria uma pasta no SD
  card.criandoArquivo("/Teste/teste.csv", "buffer_star1, buffer_star2, latitude, longitude, temperatura_motor, temperatura_cvt, velocidade, odometro, hora, minuto, mes, ano, altitude, rpm_motor, batteryLevel, farol, conct_LAN, low_gas, high_gas, buffer_end1, buffer_end2");
  card.lendoArquivo("/Teste/teste.csv");
}

void randomicString(char* buffer) {
  data.buffer_star1 = 123;
  data.buffer_star2 = 123;
  data.latitude = static_cast<float>(std::rand()) / RAND_MAX * 180.0f - 90.0f;
  data.longitude = static_cast<float>(std::rand()) / RAND_MAX * 360.0f - 180.0f;
  data.temperatura_motor = std::rand() % 60;
  data.temperatura_cvt = std::rand() % 60;
  data.velocidade = std::rand() % 60;
  data.odometro = std::rand() % 256;
  data.hora = std::rand() % 24;
  data.minuto = std::rand() % 60;
  data.mes = std::rand() % 12 + 1;
  data.ano = std::rand() % 100;  // Assumindo um valor de 0 a 99 para o ano
  data.altitude = std::rand() % 65536;
  data.rpm_motor = std::rand() % 65536;
  data.batteryLevel = std::rand() % 2;
  data.farol = std::rand() % 2;
  data.conct_LAN = std::rand() % 2;
  data.low_gas = std::rand() % 2;
  data.high_gas = std::rand() % 2;
  data.buffer_end1 = 123;
  data.buffer_end2 = 123;

  sprintf(buffer,
          "%u,%u,%.6f,%.6f,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d,%d,%u,%u",
          data.buffer_star1, data.buffer_star2, data.latitude, data.longitude,
          data.temperatura_motor, data.temperatura_cvt, data.velocidade, data.odometro,
          data.hora, data.minuto, data.mes, data.ano, data.altitude, data.rpm_motor,
          data.batteryLevel, data.farol, data.conct_LAN, data.low_gas, data.high_gas,
          data.buffer_end1, data.buffer_end2);
}


void loop() {
  tela.limparTela();
  // Simulando a recepção de dados
  randomicString(dados);
  //char *dataString = dataFunction.sensorDataToString(&data);
  card.incrementandoArquivo("/Teste/teste.csv", dados);  // Incrementa dados no arquivo
  card.lendoArquivo("/Teste/teste.csv");                 // Le a informação do Arquivo renomeado
  tela.atulizacaoTela(&data);
  tela.desenharTela();
  delay(3000);
}
