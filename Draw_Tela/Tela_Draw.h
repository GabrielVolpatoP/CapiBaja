// Cabeçalho 
// Declara funções (protótipos) para que outros arquivos saibam como utilizá-las.
#ifndef Tela_Draw_H
#define Tela_Draw_H

#include <U8g2lib.h>
#include <Arduino.h>

// ------------------------------------------------------------

class Tela_Draw {
public:
	
	void setupTela(); // Exemplo de função do display
	void atulizacaoTela(uint8_t veloc_new ,uint8_t veloc_old ,uint8_t temp_new ,uint8_t temp_old ,uint8_t odom_new ,uint8_t odom_old);
	void icons_principal();
	void backgrond_tela_principal();
	void farol();
	void draw_lora();
	void bateria();
	void gasolina();
	void atualizacao_dados(int pos_x, int pos_y, uint8_t new_data, uint8_t old_data, const uint8_t *font);
	void LimparTela();
	void ExecutarTela();
};
	
#endif // O #ifndef e #define criam uma guarda de inclusão, impedindo que o mesmo arquivo seja incluído mais de uma vez.
