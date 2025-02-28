// Implementação 
// Define como as funções trabalham e quais operações realizam.
#include "Tela_Draw.h" // Importa o cabeçalho para garantir que as declarações das funções sejam reconhecidas.

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 22); 

// ------------------------------------------------------------

void Tela_Draw::setupTela() {
    u8g2.begin();
}

// ------------------------------------------------------------

void Tela_Draw::LimparTela(){
	u8g2.clearBuffer();
}

// ------------------------------------------------------------

void Tela_Draw::ExecutarTela(){
	u8g2.clearBuffer();
	backgrond_tela_principal();
	u8g2.sendBuffer();
}

// ------------------------------------------------------------

void Tela_Draw::atulizacaoTela(uint8_t veloc_new ,uint8_t veloc_old ,uint8_t temp_new ,uint8_t temp_old ,uint8_t odom_new ,uint8_t odom_old) {

  icons_principal();        // Desenha os icones de Status

  //  Velocidade 
  atualizacao_dados(4, 46, veloc_new, veloc_old, u8g2_font_7Segments_26x42_mn);

  //  Temperatura 
  atualizacao_dados(70, 18, temp_new, temp_old, u8g2_font_VCR_OSD_mu);

  //  Odometro 
  atualizacao_dados(45, 60, odom_new, odom_old, u8g2_font_5x7_tn);
 
  // ----- Correção (Retangulo Temperatura)

  u8g2.drawFrame(66, 0, 2, 20);   // "linha" horiz sup
  u8g2.drawFrame(66, 19, 44, 2);  // "linha" vert sup
}

// ------------------------------------------------------------

void Tela_Draw::icons_principal() {  // Chama todos os elementos dos icones

  farol();     // Chama função que printa Farol
  draw_lora();      // Chama função que printa Lora
  bateria();   // Chama função que printa Bateria
  gasolina();  // Chama função que printa Gasolina
}

// ------------------------------------------------------------

void Tela_Draw::backgrond_tela_principal() {

  // Temperatura - Unidade de Medida
  u8g2.setFont(u8g2_font_8bitclassic_tf);
  u8g2.drawStr(99, 15, "c");
  u8g2.setFont(u8g2_font_6x12_mf);  // "º"
  u8g2.drawGlyph(93, 13, 0x00b0);

  // Velocidade - Unidade de Medida
  u8g2.setFont(u8g2_font_10x20_t_cyrillic);
  u8g2.drawStr(68, 46, "Km/h");

  // Odometro - Titulo
  u8g2.setFont(u8g2_font_squeezed_b6_tr);
  u8g2.drawStr(5, 60, "Odome:");

  // Odometro - Unidade de medida
  u8g2.setFont(u8g2_font_synchronizer_nbp_tf);
  u8g2.drawStr(95, 60, "Km");

  // Corpo

  u8g2.drawFrame(0, 0, 111, 50);  // Box maior

  u8g2.drawFrame(0, 50, 111, 14);  // box inferior
  u8g2.drawFrame(111, 0, 17, 64);  // lateral

  u8g2.drawFrame(66, 0, 2, 20);   // "linha" horiz sup
  u8g2.drawFrame(66, 19, 44, 2);  // "linha" vert sup
}

// ------------------------------------------------------------

void Tela_Draw::farol() {

  u8g2.drawTriangle(119, 5, 119, 15, 124, 10);  // method to build a triangle. This method accepts as arguments the coordinates of each corner and the WHITE.

  // ===================== Condicional =====================
  u8g2.drawLine(114, 7, 117, 7);    // method to create a line
  u8g2.drawLine(114, 10, 117, 10);  // method to create a line
  u8g2.drawLine(114, 13, 117, 13);  // method to create a line
}

// ------------------------------------------------------------

void Tela_Draw::draw_lora() {

  u8g2.drawLine(115, 20, 122, 20);  // method to create a line
  u8g2.drawPixel(114, 21);          // plot a pixel in the x,y coordinates
  u8g2.drawPixel(123, 21);          // plot a pixel in the x,y coordinates

  u8g2.drawLine(116, 22, 121, 22);  // method to create a line
  u8g2.drawPixel(115, 23);          // plot a pixel in the x,y coordinates
  u8g2.drawPixel(122, 23);          // plot a pixel in the x,y coordinates

  u8g2.drawLine(117, 24, 120, 24);  // method to create a line
  u8g2.drawPixel(116, 25);          // plot a pixel in the x,y coordinates
  u8g2.drawPixel(121, 25);          // plot a pixel in the x,y coordinates

  u8g2.drawFrame(118, 26, 2, 2);  // provides an easy way to draw a rectangle
}

// ------------------------------------------------------------

void Tela_Draw::bateria() {

  u8g2.drawFrame(117, 32, 4, 2);   // provides an easy way to draw a rectangle
  u8g2.drawFrame(115, 34, 8, 10);  // provides an easy way to draw a rectangle

  // ===================== Condicional =====================
  u8g2.drawBox(117, 36, 4, 6);  // provides an easy way to draw a rectangle
}

// ------------------------------------------------------------

void Tela_Draw::gasolina() {

  u8g2.drawFrame(115, 50, 7, 9);    // provides an easy way to draw a rectangle
  u8g2.drawLine(114, 48, 118, 48);  // method to create a line
  u8g2.drawLine(121, 50, 123, 50);  // method to create a line
  u8g2.drawPixel(114, 49);          // plot a pixel in the x,y coordinates
  u8g2.drawPixel(119, 49);          // plot a pixel in the x,y coordinates
  u8g2.drawPixel(124, 51);          // plot a pixel in the x,y coordinates

  // ===================== Condicional =====================
  u8g2.drawBox(117, 52, 3, 5);  // provides an easy way to draw a rectangle
}

// ------------------------------------------------------------

void Tela_Draw::atualizacao_dados(int pos_x, int pos_y, uint8_t new_data, uint8_t old_data, const uint8_t *font) {
  u8g2.setFont(font);
  u8g2.setCursor(pos_x, pos_y);
  if (new_data != old_data) {
    u8g2.print(new_data);
  } else {
    u8g2.print(old_data);
  }
}
