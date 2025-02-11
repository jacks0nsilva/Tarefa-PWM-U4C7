# Tarefa-PWM-U4C7

## Visão Geral 🌐

Esta tarefa demonstra o controle de um servomotor utilizando PWM (Pulse Width Modulation) em uma placa Raspberry Pi Pico. O programa posiciona o servomotor em ângulos específicos (0°, 90° e 180°) e, em seguida, realiza um movimento suave oscilando entre 0° e 180°.

## Vídeo de apresentação 🎥

[Vídeo de apresentação do projeto](link_do_video)

## Funcionalidades 📌

- Configuração do PWM para operar a 50Hz (período de 20ms).
- Cálculo do wrap e definição do divisor de clock para gerar o sinal PWM.
- Movimento inicial para posições fixas:
  - 180°: pulso de 2400µs.
  - 90°: pulso de 1470µs.
  - 0°: pulso de 500µs.
- Movimento contínuo suave, aumentando e diminuindo gradualmente o pulso aplicado ao servomotor.

## Arquivos Principais

- Tarefa-PWM-U4C7.c: Contém a implementação em C que configura o PWM, define as posições do servomotor e executa os movimentos.

## Requisitos

- Hardware:
  - Raspberry Pi Pico
  - Servomotor conectado à GPIO 22 (definida em SERVO_PIN)
  - LED azul (definido em LED_BLUE - GPIO 12)
- Software:
  - Pico SDK instalado e configurado
  - Ferramentas de compilação (CMake, Make, etc)

## Funcionamento do Código

1. **Inicialização e Configuração**
   - A função `stdio_init_all()` inicializa os recursos de I/O padrão.
   - O pino do servomotor é configurado como saída PWM usando `gpio_set_function()`.
   - É obtido o slice PWM relacionado ao pino com `pwm_gpio_to_slice_num()`.
2. **Configuração do PWM**

   - Na função `pwm_setup()`, o PWM é configurado para operar com um divisor de clock (CLOCK_DIV) e frequência definida (PWM_FREQ).
   - O "wrap" é calculado a partir da frequência do clock do sistema e do divisor, permitindo a definição correta do período do PWM.

3. **Controle do Servomotor**
   - A função `set_servo_position()` calcula o nível do PWM (o duty cycle) com base no pulso em microsegundos desejado.
   - O programa inicialmente move o servomotor para posições fixas de 180°, 90° e 0°, com intervalos de 5 segundos.
   - Em seguida, entra em um loop infinito onde o servomotor oscila suavemente entre 0° e 180° (e vice-versa) aumentando e diminuindo gradualmente o pulso aplicado.

## Experimento com o LED

- Conforme solicitado, foi realizado um exprimento com o LED azul (GPIO 12) utilizando o código dessa tarefa. Foi constatado que o LED diminui bastante a sua luminosidade ao logo dos primeiros 15 segundos mas não se apaga completamente, logo mais ele entra em um ciclo de aumentar e diminuir a luminosidade suavemente.

## Compilação e Execução

_Obs: É necessário ter a exntesão do Wokwi instalado no VsCode_

1.  **Clone o repositório**
    ```
    git clone https://github.com/jacks0nsilva/Tarefa-UART-I2C
    ```
2.  **Instale a extensão do Raspberry Pi Pico no seu VsCode**
3.  **Usando a extensão do Raspberry Pi Pico, siga os passos:**
4.  **Clean CMake: Para garantir que o projeto será compilado do zero**

5.  **Compile Project: Compilação dos binários**

6.  **Abra o arquivo diagram.json para iniciar o simulador**
