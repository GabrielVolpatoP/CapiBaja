<header>
<h2> Fluxograma Principal 
  
<img src="https://img.shields.io/badge/READ%20ME-555555" alt="ReadMe" align="right"  width="q35">
</h2>
</header>

<br>

```txt

    Início
      |
      v
    Setup
      |
      +----------------------+
      |                      |
      v                      v
    receiverTask          displayTask
      |                      |
      v                      v
    Coletar Dados         Receber Dados
      |                      |
      v                      v
    Enviar para Fila     Atualizar Tela
      |                      |
      v                      v
    Escrever no SD
      |
      v
    Enviar via LoRa
      |
      v
    Atraso 100ms
      |
      v
    Repetir

```

### Início: 
O programa começa com a função ``setup()``, onde são inicializados os componentes e criadas as tarefas.

### Setup:

- Inicializa a comunicação Serial e LoRa.
- Configura a tela e o cartão SD.
- Cria uma fila para armazenar dados de sensores.
- Cria duas tarefas: receiverTask e displayTask.

### Tarefas:

- **receiverTask**
  - Coleta dados dos sensores.
  - Envia dados para a fila.
  - Escreve dados no cartão SD.
  - Envia dados via LoRa.
  - Atraso de 100ms.

- **displayTask**
  - Recebe dados da fila.
  - Atualiza a tela com os dados recebidos.

### Loop: 
O loop principal fica vazio, pois todas as operações são gerenciadas pelas tarefas FreeRTOS.

