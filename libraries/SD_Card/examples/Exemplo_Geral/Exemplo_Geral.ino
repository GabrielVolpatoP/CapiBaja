#include <SD_Card.h>

SD_Card Card;

// ------------------------------------------------------------

void setup() {

  Card.setup();

  Serial.println(" _ _ _ _ INÍCIO DO PROGRAMA _ _ _ _ _");

  Card.lista_Diretorio(SD, "/", 0);                                   // Faz a triagem do SD
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.criando_Diretorio(SD, "/mydir");                               // Cria uma pasta no SD
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.lista_Diretorio(SD, "/", 0);                                   // Listagem para ver a criação
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.apagando_Diretorio(SD, "/mydir");                              // Apaga a Pasta
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.lista_Diretorio(SD, "/", 2);                                   // Listagem para ver o delete
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.criando_Arquivo(SD, "/hello.csv", "Dado1");                    // Cria o arquivo (aqui ja com valor)
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.lendo_Arquivo(SD, "/hello.csv");                               // Le a informação do Arquivo
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.incrementando_Arquivo(SD, "/hello.csv", "Dado2,Dado3,Dado4");  // Incrementa dados no arquivo
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.lendo_Arquivo(SD, "/hello.csv");                               // Le a informação do Arquivo
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.deletando_arquivo(SD, "/foo.csv");                             // Deleta um arquivo que nao existe para teste
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.renomeando_Arquivo(SD, "/hello.csv", "/foo.csv");              // Renomeia o arquivo
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.lendo_Arquivo(SD, "/foo.csv");                                 // Le a informação do Arquivo renomeado
  Serial.println("__");                                               // So para ficar mais facil de saber as etapas
  Card.armazenamento_Geral(SD);                                       // Exibe o espaço Total e Usado do SDcard
}

void loop() {
}