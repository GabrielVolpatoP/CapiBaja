// Implementação 
// Define como as funções trabalham e quais operações realizam.
#include "SD_Card.h" // Importa o cabeçalho para garantir que as declarações das funções sejam reconhecidas.
#include "FS.h"
#include "SD.h"
#include "SPI.h"

// Definição dos novos pinos SPI para o SD Card
#define SD_SCK   14  // Clock
#define SD_MISO  12  // Entrada de dados
#define SD_MOSI  13  // Saída de dados
#define SD_CS    27   // Chip Select (ajuste conforme necessário)
#define SERIAL_BAUD_RATE 115200

// ------------------------------------------------------------

void SD_Card::setup(){
  Serial.begin(SERIAL_BAUD_RATE);
  if(!SD.begin(SD_CS)){
    Serial.println("Falha ao montar o cartão SD");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("Nenhum cartão SD conectado");
    return;
  }

}

// ------------------------------------------------------------

void SD_Card::lista_Diretorio(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listando diretórios: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Falha ao abrir diretório");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Não é um diretório");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  PASTA   : ");
      Serial.println(file.name());
      if(levels){
        lista_Diretorio(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  ARQUIVO: ");
      Serial.print(file.name());
      Serial.print("  TAMANHO: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

// ------------------------------------------------------------

void SD_Card::criando_Diretorio(fs::FS &fs, const char * path){
  Serial.printf("Criando diretório: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Diretório criado");
  } else {
    Serial.println("Falha ao criar diretório");
  }
}

// ------------------------------------------------------------

void SD_Card::apagando_Diretorio(fs::FS &fs, const char * path){
  Serial.printf("Removendo diretório: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Diretório removido");
  } else {
    Serial.println("Falha ao remover diretório");
  }
}

// ------------------------------------------------------------

void SD_Card::lendo_Arquivo(fs::FS &fs, const char * path){
  Serial.printf("Lendo arquivo: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Falha ao abrir arquivo para leitura");
    return;
  }

  Serial.print("Conteúdo do arquivo: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

// ------------------------------------------------------------

void SD_Card::criando_Arquivo(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Escrevendo arquivo: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Falha ao abrir arquivo para escrita");
    return;
  }
  if(file.print(message)){
    file.print("\n");
    Serial.println("Arquivo escrito");
  } else {
    Serial.println("Falha na escrita");
  }
  file.close();
}

// ------------------------------------------------------------

void SD_Card::incrementando_Arquivo(fs::FS &fs, const char * path, const char * message){
  //Serial.printf("Adicionando ao arquivo: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Falha ao abrir arquivo para adicionar conteúdo");
    return;
  }
  if(file.print(message)){
      Serial.println("Mensagem adicionada");
      file.print("\n"); // Pula linhas CSV
  } else {
    Serial.println("Falha ao adicionar conteúdo");
  }
  file.close();
}

// ------------------------------------------------------------

void SD_Card::renomeando_Arquivo(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renomeando arquivo de %s para %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("Arquivo renomeado");
  } else {
    Serial.println("Falha ao renomear arquivo");
  }
}

// ------------------------------------------------------------

void SD_Card::deletando_arquivo(fs::FS &fs, const char * path){
  Serial.printf("Deletando arquivo: %s\n", path);
  if(fs.remove(path)){
    Serial.println("Arquivo deletado");
  } else {
    Serial.println("Falha ao deletar arquivo");
  }
}

// ------------------------------------------------------------

void SD_Card::teste_Geral(fs::FS &fs, const char * path){
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file){
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len){
      size_t toRead = len;
      if(toRead > 512){
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes lidos em %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Falha ao abrir arquivo para leitura");
  }

  file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Falha ao abrir arquivo para escrita");
    return;
  }

  size_t i;
  start = millis();
  for(i=0; i<2048; i++){
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes escritos em %u ms\n", 2048 * 512, end);
  file.close();
}

// ------------------------------------------------------------

void SD_Card::armazenamento_Geral(fs::FS &fs){
    Serial.printf("Espaço total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Espaço usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}
