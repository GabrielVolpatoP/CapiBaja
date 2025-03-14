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
	void apagandoDiretorio(const char * path);
	void armazenamentoGeral();
	void criandoArquivo(const char * path, const char * message);
	void criandoDiretorio(const char * path);
	void deletandoArquivo(const char * path);
	void incrementandoArquivo(const char * path, const char * message);
	void lendoArquivo(const char * path);
	void listaDiretorio(const char *dirname, uint8_t levels);
	void renomeandoArquivo(const char * path1, const char * path2);
	void testeGeral(const char * path);
	
};

#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.
