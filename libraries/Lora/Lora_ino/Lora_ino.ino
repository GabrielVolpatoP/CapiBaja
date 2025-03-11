#define RXD2 19  // GPIO17 (RX2) - Recebe dados do LoRa
#define TXD2 21  // GPIO16 (TX2) - Transmite dados para o LoRa
#define SERIAL_BAUD_RATE 115200
#define LORA_BAUD_RATE 115200

HardwareSerial lora(2);  // Define UART2

// Number of variables expected
const int numVars = 10;
int vars[numVars];  // Array to hold parsed integers

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);  // Comunicação com o PC
  lora.begin(LORA_BAUD_RATE, SERIAL_8N1, RXD2, TXD2);  // Configura UART2 nos pinos 16 e 17 com 115200 baud
}

void analiseMensagem(const String &mensagem) {
  int startIndex = 0;
  int endIndex;
  for (int i = 0; i < numVars; ++i) {
    endIndex = mensagem.indexOf(',', startIndex);
    if (endIndex == -1) {
      endIndex = mensagem.length();
    }
    vars[i] = mensagem.substring(startIndex, endIndex).toInt();
    startIndex = endIndex + 1;
  }
}

void loop() {
  if (lora.available()) {  // Verifica se há dados recebidos
    String mensagem = lora.readString();  // Lê a string recebida
    // Exemplo: "10,20,30,40,50,60,70,80,90,100"
    mensagem.trim();  // Remover o caractere de nova linha ou retorno de carro se existir

    // Check if the message has the correct number of variables
    int commaCount = mensagem.length() - mensagem.replace(",", "").length();
    if (commaCount != numVars - 1) {
      Serial.println("Erro: Mensagem mal formatada");
      return;
    }

    analiseMensagem(mensagem);

    if (vars[0] == 10 && vars[1] == 20 && vars[8] == 90 && vars[9] == 100) {
      // Exibe os valores no monitor serial
      Serial.print("var1: ");
      Serial.println(vars[0]);
      Serial.print("var2: ");
      Serial.println(vars[1]);
      Serial.print("rpm: ");
      Serial.println(vars[2]);
      Serial.print("gps: ");
      Serial.println(vars[3]);
      Serial.print("temp_motor: ");
      Serial.println(vars[4]);
      Serial.print("temp_cvt: ");
      Serial.println(vars[5]);
      Serial.print("comb: ");
      Serial.println(vars[6]);
      Serial.print("vel: ");
      Serial.println(vars[7]);
      Serial.print("Var9: ");
      Serial.println(vars[8]);
      Serial.print("Var10: ");
      Serial.println(vars[9]);
      Serial.println("------------------------------------------------");
    }
  }
}