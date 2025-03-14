// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef SD_Card_H
#define SD_Card_H

#include <FS.h>
#include <SD.h>
#include <SPI.h>

// ------------------------------------------------------------

class SD_Card {
public:
	void setup();
	void apagando_Diretorio(const char * path);
	void armazenamento_Geral();
	void criando_Arquivo(const char * path, const char * message);
	void criando_Diretorio(const char * path);
	void deletando_arquivo(const char * path);
	void incrementando_Arquivo(const char * path, const char * message);
	void lendo_Arquivo(const char * path);
	void lista_Diretorio(const char *dirname, uint8_t levels);
	void renomeando_Arquivo(const char * path1, const char * path2);
	void teste_Geral(const char * path);
	
};

#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.
