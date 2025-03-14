#include <SD_Card.h>
SD_Card card;

int dado1, dado2, dado3;
char dados[50];

void setup() {
  card.setup();

  Serial.println(" _ _ _ _ INÍCIO DO PROGRAMA _ _ _ _ _");
  gerarDados(dados);
  card.lista_Diretorio("/", 1);  // Faz a triagem do SD
  Serial.println("__");
  card.criando_Diretorio("/Dados");  // Cria uma pasta no SD
  Serial.println("__");
  card.lista_Diretorio("/", 1);  // Listagem para ver a criação
  Serial.println("__");
  card.apagando_Diretorio("/Dados");  // Apaga a Pasta
  Serial.println("__");
  card.lista_Diretorio("/", 1);  // Listagem para ver o delete
  Serial.println("__");
  card.criando_Diretorio("/Dados");  // Cria uma pasta no SD
  Serial.println("__");
  card.criando_Arquivo("/Dados/dados.csv", dados);  // Cria o arquivo (aqui ja com valor)
  Serial.println("__");
  card.lendo_Arquivo("/Dados/dados.csv");  // Le a informação do Arquivo
  Serial.println("__");
  gerarDados(dados);                                      // Gera valores aleatorios para teste
  card.incrementando_Arquivo("/Dados/dados.csv", dados);  // Incrementa dados no arquivo
  gerarDados(dados);                                      // Gera valores aleatorios para teste
  card.incrementando_Arquivo("/Dados/dados.csv", dados);  // Incrementa dados no arquivo
  gerarDados(dados);                                      // Gera valores aleatorios para teste
  card.incrementando_Arquivo("/Dados/dados.csv", dados);  // Incrementa dados no arquivo
  gerarDados(dados);                                      // Gera valores aleatorios para teste
  card.incrementando_Arquivo("/Dados/dados.csv", dados);  // Incrementa dados no arquivo
  Serial.println("__");
  card.lendo_Arquivo("/Dados/dados.csv");  // Le a informação do Arquivo
  Serial.println("__");
  card.deletando_arquivo("/Dados/teste.csv");  // Deleta um arquivo que nao existe para teste
  Serial.println("__");
  card.renomeando_Arquivo("/Dados/dados.csv", "/Dados/teste.csv");  // Renomeia o arquivo
  Serial.println("__");
  card.lendo_Arquivo("/Dados/teste.csv");  // Le a informação do Arquivo renomeado
  Serial.println("__");
  card.lista_Diretorio("/", 1);
  Serial.println("__");
  card.armazenamento_Geral();  // Exibe o espaço Total e Usado do SDcard
}

void gerarDados(char* buffer) {
  dado1 = random(0, 300);  // Gera um valor inteiro aleatorio entre 0 e 300
  dado2 = random(0, 300);  // Gera um valor inteiro aleatorio entre 0 e 300
  dado3 = random(0, 300);  // Gera um valor inteiro aleatorio entre 0 e 300

  sprintf(buffer, "%d, %d, %d", dado1, dado2, dado3);
}

void loop() {
}