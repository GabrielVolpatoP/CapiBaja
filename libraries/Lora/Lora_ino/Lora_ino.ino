#define RXD2 19  // GPIO17 (RX2) - Recebe dados do LoRa
#define TXD2 21  // GPIO16 (TX2) - Transmite dados para o LoRa

HardwareSerial lora(2);  // Define UART2

// Declaração das 10 variáveis
int var1, var2, var3, var4, var5, var6, var7, var8, var9, var10;

void setup() {
  Serial.begin(115200);  // Comunicação com o PC
  lora.begin(115200, SERIAL_8N1, RXD2, TXD2);  // Configura UART2 nos pinos 16 e 17 com 115200 baud
}

void loop() {
  if (lora.available()) {  // Verifica se há dados recebidos
    String mensagem = lora.readString();  // Lê a string recebida
    // Exemplo: "10,20,30,40,50,60,70,80,90,100"
    
    // Remover o caractere de nova linha ou retorno de carro se existir
    mensagem.trim(); 

    // Separando os dados em variáveis, utilizando vírgula como delimitador
    int startIndex = 0;
    int endIndex = mensagem.indexOf(',');

    var1 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var1
    startIndex = endIndex + 1;
    endIndex = mensagem.indexOf(',', startIndex);
    
    var2 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var2
    startIndex = endIndex + 1;
    endIndex = mensagem.indexOf(',', startIndex);

    if(var1 == 10 && var2 == 20){
      
      var3 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var3
      startIndex = endIndex + 1;
      endIndex = mensagem.indexOf(',', startIndex);
  
      var4 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var4
      startIndex = endIndex + 1;
      endIndex = mensagem.indexOf(',', startIndex);
      
      var5 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var5
      startIndex = endIndex + 1;
      endIndex = mensagem.indexOf(',', startIndex);
  
      var6 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var6
      startIndex = endIndex + 1;
      endIndex = mensagem.indexOf(',', startIndex);
      
      var7 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var7
      startIndex = endIndex + 1;
      endIndex = mensagem.indexOf(',', startIndex);
  
      var8 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var8
      startIndex = endIndex + 1;
      endIndex = mensagem.indexOf(',', startIndex);
      
    }
    
    var9 = mensagem.substring(startIndex, endIndex).toInt();  // Converte a substring para inteiro e armazena em var9
    startIndex = endIndex + 1;
    endIndex = mensagem.indexOf(',', startIndex);

    var10 = mensagem.substring(startIndex).toInt();  // Para o último valor, não há vírgula após ele

   if(var9 == 90 && var10 == 100){
    
      // Exibe os valores no monitor serial
      Serial.print("var1: ");
      Serial.println(var1);
      Serial.print("var2: ");
      Serial.println(var2);
      Serial.print("rpm: ");
      Serial.println(var3);
      Serial.print("gps: ");
      Serial.println(var4);
      Serial.print("temp_motor: ");
      Serial.println(var5);
      Serial.print("temp_cvt: ");
      Serial.println(var6);
      Serial.print("comb: ");
      Serial.println(var7);
      Serial.print("vel: ");
      Serial.println(var8);
      Serial.print("Var9: ");
      Serial.println(var9);
      Serial.print("Var10: ");
      Serial.println(var10);
      Serial.println("------------------------------------------------");
      
   }
  }
}
