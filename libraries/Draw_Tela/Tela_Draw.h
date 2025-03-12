// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef Tela_Draw_H
#define Tela_Draw_H

#include <U8g2lib.h>
#include "Sensor_Data.h"

// ------------------------------------------------------------

class Tela_Draw {
public:
	void setup(); // Configura o display e desenha os ícones principais e o fundo da tela.

	void atulizacaoTela(SensorData* sensorData);
	// Atualiza os dados na tela para velocidade, temperatura e odômetro, e corrige a linha horizontal superior.

	void iconsPrincipal(); // Desenha os ícones principais na tela (farol, Lora, bateria, gasolina).

	void backgrondTela(); // Desenha o fundo da tela, incluindo unidades de medida e caixas.

	void iconFarol(); // Desenha o ícone de farol na tela.

	void iconLora(); // Desenha o ícone de Lora na tela.

	void iconBateria(); // Desenha o ícone de bateria na tela.

	void iconGasolina(); // Desenha o ícone de gasolina na tela.

	void inserirVariavel(int pos_x, int pos_y, uint8_t new_data, uint8_t old_data, const uint8_t *font);
	// Insere variáveis na tela, atualizando o valor se houver uma diferença significativa entre o novo e o antigo.

	void limparTela(); // Limpa o buffer da tela.

	void desenharTela(); // Envia o buffer para o display, desenhando o conteúdo na tela.
};
	
#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.
