// Implementação 
// Define como as funções trabalham e quais operações realizam.
#include "Lora.h" // Importa o cabeçalho para garantir que as declarações das funções sejam reconhecidas.
#include "Sensor_Data.h"

#define RXD2 19  // GPIO17 (RX2) - Recebe dados do LoRa 
#define TXD2 21  // GPIO16 (TX2) - Transmite dados para o LoRa
#define SERIAL_BAUD_RATE 115200
#define LORA_BAUD_RATE 115200
#define DATA_SEND_INTERVAL 1100

HardwareSerial lora(2);  // Define UART2
unsigned long previousMillis = 0;
String mensagem;

// ------------------------------------------------------------

// Criando as tarefas <Dual>
void Lora::setup(){
	Serial.begin(SERIAL_BAUD_RATE);  // Comunicação com o PC
	lora.begin(LORA_BAUD_RATE, SERIAL_8N1, RXD2, TXD2);  // Configura UART2 nos pinos 16 e 17 com 115200 baud
}

// ------------------------------------------------------------

void Lora::analiseMensagem(SensorData* dados) {
    if (lora.available()) {  // Verifica se há dados recebidos
        String mensagem = lora.readString();  // Lê a string recebida
        // Exemplo: "1,1,37.7749,-122.4194,10,20,30,40,12,30,3,2023,100,5000,1,1,1,0,0,1,1"
        mensagem.trim();  // Remover o caractere de nova linha ou retorno de carro se existir

        // Verifica se a mensagem tem o número correto de variáveis
        int commaCount = 0;
        for (int i = 0; i < mensagem.length(); i++) {
            if (mensagem.charAt(i) == ',') {
                commaCount++;
            }
        }
        
        if (commaCount != 20) {
            Serial.println("Erro: Mensagem mal formatada");
            return;
        }

        int startIndex = 0;
        int endIndex;
        String valores[21];  // Array para armazenar as partes da mensagem

        // Divide a mensagem em partes
        for (int i = 0; i < 21; ++i) {
            endIndex = mensagem.indexOf(',', startIndex);
            if (endIndex == -1) {
                endIndex = mensagem.length();
            }
            valores[i] = mensagem.substring(startIndex, endIndex);
            startIndex = endIndex + 1;
        }

        // Converte as partes para os tipos corretos e armazena na estrutura
        dados->buffer_star1 = valores[0].toInt();
        dados->buffer_star2 = valores[1].toInt();
        dados->latitude = valores[2].toFloat();
        dados->longitude = valores[3].toFloat();
        dados->temperatura_motor = valores[4].toInt();
        dados->temperatura_cvt = valores[5].toInt();
        dados->velocidade = valores[6].toInt();
        dados->odometro = valores[7].toInt();
        dados->hora = valores[8].toInt();
        dados->minuto = valores[9].toInt();
        dados->mes = valores[10].toInt();
        dados->ano = valores[11].toInt();
        dados->altitude = valores[12].toInt();
        dados->rpm_motor = valores[13].toInt();
        dados->batteryLevel = valores[14].toInt() == 1;
        dados->farol = valores[15].toInt() == 1;
        dados->conct_LAN = valores[16].toInt() == 1;
        dados->low_gas = valores[17].toInt() == 1;
        dados->high_gas = valores[18].toInt() == 1;
        dados->buffer_end1 = valores[19].toInt();
        dados->buffer_end2 = valores[20].toInt();
    }
}

// ------------------------------------------------------------


void Lora::printMensagemTeste(SensorData* dados){
	analiseMensagem(dados);
	
	// Exibe os valores no monitor serial
	Serial.print("Buffer Start 1: ");
	Serial.println(dados->buffer_star1);
	Serial.print("Buffer Start 2: ");
	Serial.println(dados->buffer_star2);
	Serial.print("Latitude: ");
	Serial.println(dados->latitude, 6);
	Serial.print("Longitude: ");
	Serial.println(dados->longitude, 6);
	Serial.print("Temperatura Motor: ");
	Serial.println(dados->temperatura_motor);
	Serial.print("Temperatura CVT: ");
	Serial.println(dados->temperatura_cvt);
	Serial.print("Velocidade: ");
	Serial.println(dados->velocidade);
	Serial.print("Odômetro: ");
	Serial.println(dados->odometro);
	Serial.print("Hora: ");
	Serial.println(dados->hora);
	Serial.print("Minuto: ");
	Serial.println(dados->minuto);
	Serial.print("Mês: ");
	Serial.println(dados->mes);
	Serial.print("Ano: ");
	Serial.println(dados->ano);
	Serial.print("Altitude: ");
	Serial.println(dados->altitude);
	Serial.print("RPM Motor: ");
	Serial.println(dados->rpm_motor);
	Serial.print("Nível da bateria: ");
	Serial.println(dados->batteryLevel ? "Sim" : "Não");
	Serial.print("Farol: ");
	Serial.println(dados->farol ? "Ligado" : "Desligado");
	Serial.print("Conexão LAN: ");
	Serial.println(dados->conct_LAN ? "Conectado" : "Desconectado");
	Serial.print("Gasolina baixa: ");
	Serial.println(dados->low_gas ? "Sim" : "Não");
	Serial.print("Gasolina alta: ");
	Serial.println(dados->high_gas ? "Sim" : "Não");
	Serial.print("Buffer End 1: ");
	Serial.println(dados->buffer_end1);
	Serial.print("Buffer End 2: ");
	Serial.println(dados->buffer_end2);
	Serial.println("------------------------------------------------");
}

void Lora::sendDataToLora(SensorData* dados) {
  if (millis() - previousMillis >= DATA_SEND_INTERVAL) {
    previousMillis = millis();
    char data[128];
    snprintf(data, sizeof(data), "OMELHORBAJA, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
             dados->low_gas, dados->high_gas, dados->farol, dados->batteryLevel,
             dados->temperatura_motor, dados->rpm_motor, dados->velocidade, dados->odometro,
             dados->hora, dados->minuto, dados->mes, dados->ano);
    lora.print(data);
  }
}