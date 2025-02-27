// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef SD_Card_H
#define SD_Card_H

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include "sd_defines.h"

// ------------------------------------------------------------

class SD_Card {
public:
	void setup();
	void apagando_Diretorio(fs::FS &fs, const char * path);
	void armazenamento_Geral(fs::FS &fs);
	void criando_Arquivo(fs::FS &fs, const char * path, const char * message);
	void criando_Diretorio(fs::FS &fs, const char * path);
	void deletando_arquivo(fs::FS &fs, const char * path);
	void incrementando_Arquivo(fs::FS &fs, const char * path, const char * message);
	void lendo_Arquivo(fs::FS &fs, const char * path);
	void lista_Diretorio(fs::FS &fs, const char *dirname, uint8_t levels);
	void renomeando_Arquivo(fs::FS &fs, const char * path1, const char * path2);
	void teste_Geral(fs::FS &fs, const char * path);
	
};

#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.
