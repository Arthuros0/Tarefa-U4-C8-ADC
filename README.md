# Tarefa: Controle de LEDs e Joystick com RP2040

Este repositório contém o código e documentação do projeto desenvolvido para explorar conversores A/D e funcionalidades do RP2040 usando a placa BitDogLab.

## Objetivos
- Compreender o funcionamento do conversor analógico-digital (ADC).
- Controlar LEDs RGB com PWM baseado nos valores de um joystick.
- Representar graficamente a posição do joystick no display SSD1306 via protocolo I2C.

## **Vídeo de Demonstração do Projeto**
Confira a demonstração da tarefa clicando no ícone abaixo:

<a href="https://youtube.com/shorts/1kPjNn21gPU">
  <img src="https://img.icons8.com/color/48/000000/youtube-play.png" alt="YouTube" />
</a>


## Funcionalidades
- **Controle de LEDs RGB**:
  - Brilho do LED Azul ajustado pelo eixo Y do joystick.
  - Brilho do LED Vermelho ajustado pelo eixo X do joystick.
- **Display SSD1306**:
  - Movimento de um quadrado de 8x8 pixels, proporcional à posição do joystick.
- **Botão do joystick**:
  - Alterna o estado do LED Verde.
  - Modifica a borda do display.
- **Botão A**:
  - Ativa/desativa os LEDs RGB.

## Requisitos Técnicos
1. **Interrupções (IRQ)**: Todos os botões utilizam rotinas de interrupção.
2. **Debouncing**: Tratamento de bouncing implementado via software.
3. **Display 128x64**: Integração gráfica utilizando protocolo I2C.
4. **Estruturação do código**: Código limpo, modular e comentado.

## Componentes Utilizados
- LED RGB (GPIOs 11, 12, 13)
- Joystick (GPIOs 26, 27 e botão GPIO 22)
- Botão A (GPIO 5)
- Display SSD1306 (GPIOs 14 e 15, via I2C)

 ### **Pré-requisitos para utilização**
Certifique-se de que os seguintes itens estão instalados:

1. **Visual Studio Code**  
   - Ambiente de desenvolvimento integrado (IDE) para edição, compilação e depuração do código.

2. **Git**  
   - Ferramenta para versionamento de código e controle de repositórios.  

3. **Extensões do Visual Studio Code**  
   - **C/C++**: Suporte à linguagem C/C++ para análise de código, depuração e IntelliSense.  
   - **CMake Tools**: Para gerenciar e configurar projetos que utilizam o CMake.  
   - **Raspberry Pi Pico**: Extensão para facilitar o desenvolvimento e a comunicação com a placa Raspberry Pi Pico.  

4. **Zadig**  
   - Software necessário para instalar drivers USB.  
   - Permite a conexão via USB da placa Raspberry Pi Pico com o desktop ou notebook.  

5. **Versão 2.0.0+ do Raspberry Pi Pico SDK**  
   - Certifique-se de que a versão 2.0.0 ou superior do SDK para Raspberry Pi Pico está instalada.  
---
## 🚀 Como Executar

### **1. Configuração Inicial**
1. Certifique-se de que todas as dependências acima estão instaladas no seu computador.
2. Clone o repositório do projeto usando os comandos abaixo no terminal:  
   ```bash
   git init
   ```
   ```bash
   git clone https://github.com/Arthuros0/Tarefa-U4-C8-ADC.git
   ```
3. Abra o projeto clonado no VS Code

### **2. Compilação e Carregamento na Placa**
1. Compile o projeto clicando na opção "**Compile Project**" da extensão Raspberry Pi Pico no **Visual Studio Code**.
2. Após a compilação bem-sucedida, conecte a Raspberry Pi Pico W ao computador utilizando um cabo USB.
3. Coloque a placa em modo **BootSel**:
   - Pressione e segure o botão **BOOTSEL** enquanto conecta a placa pelo cabo USB.
   - Caso esteja utilizando a BitDogLab, aperte o botão **RESET** enquanto pressiona e segura o botão **BOOTSEL** (este método não exige a reconexão do cabo USB) 
4. Localize o arquivo gerado com extensão .uf2 (como **tarefa_adc.uf2**) e arraste-o para o dispositivo que aparecerá no computador. Ou selecione a opção "**Run Project(USB)**" da extensão Raspberry Pi Pico no **Visual Studio Code**.

