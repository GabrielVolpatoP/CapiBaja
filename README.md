<header>
<h2> Programa 
<img src="https://img.shields.io/badge/READ%20ME-555555" alt="ReadMe" align="right"  width="q35">
</h2>
</header>

> [!IMPORTANT]\
> **Faça download da versão main e execute o arquivo**  ```Include_Library.bat``` **ele vai incluir as bliotecas no Arduino IDE**

<br>

As bibliotecas presentes em ```"libraries"``` devem se encontrar na pasta padrão do Arduino IDE, junto as outras bibliotecas, o esquema abaixo mostra a posição qual devem se encontrar:

```txt
  C:\Users\NameUser\Documents
  │
  │── libraries/
        │
        │── Draw_Tela/...
        │── SD_Card/...
        │── Dual_Nucle/...
```

<br>

*"Projeto/Projeto.ino", podem estar em qualquer lugar do computador*

## Descrição do Projeto
Este projeto visa desenvolver um sistema de monitoramento e controle para o veículo Baja SAE, utilizando um ESP32 para coletar dados de sensores, exibir informações em uma tela e armazenar dados em um cartão SD.

## Pré-requisitos
**Geral:**
- Arduino IDE instalado
- ESP32
- Módulo SD Card
- Módulo Lora
- Display LCD12864
  
**Bibliotecas:**
- [U8g2](https://github.com/olikraus/u8g2)

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).

## Autores
- Gabriel Volpato

## Contato
Para suporte ou dúvidas, entre em contato pelo email: volpatocursin@outlook.com
