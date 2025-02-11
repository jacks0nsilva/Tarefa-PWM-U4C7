#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM
#include "hardware/clocks.h" //biblioteca para manipulação de clocks

#define SERVO_PIN 22 // Pino do servomotor conectado à GPIO como PWM
#define PWM_FREQ 50  // 50Hz -> período de 20ms
#define CLOCK_DIV 64.0f // Divisor do clock para o PWM
#define LED_BLUE 12 // Pino do LED azul

// Função para configurar o módulo PWM
void pwm_setup(uint slice) {
    pwm_set_clkdiv(slice, CLOCK_DIV); // Define o divisor de clock do PWM
    uint32_t clock_freq = clock_get_hz(clk_sys); // Frquência padrão de 125MHz
    uint32_t wrap = (clock_freq / CLOCK_DIV) / PWM_FREQ - 1; // WRAP = 39061
    pwm_set_wrap(slice, wrap);
    pwm_set_enabled(slice, true); // Habilita o PWM

    printf("Frequência do Clock do Sistema: %u Hz\n", clock_freq);
    printf("Divisor de Clock PWM: %f\n", CLOCK_DIV);
    printf("Frequência PWM Calculada: %f Hz\n", (float)clock_freq / CLOCK_DIV / (wrap + 1));
    printf("Valor de Wrap PWM: %u\n", wrap);
}

// Função para definir posição do servo
void set_servo_position(uint slice, uint16_t pulse_width_us) {
    // Obtém a frequência do clock do sistema (125 MHz por padrão)
    uint32_t clock_freq = clock_get_hz(clk_sys);
    // Calcula o valor máximo do contador PWM (wrap), baseado na frequência desejada (50 Hz)
    uint32_t wrap = (clock_freq / CLOCK_DIV) / PWM_FREQ - 1;

    // Converte o tempo de pulso (em microssegundos) para o valor do nível PWM
    // Multiplica pelo número total de contagens do PWM (wrap + 1) e divide pelo período total (20ms)
    uint32_t level = (pulse_width_us * (wrap + 1)) / 20000;

    // Define o nível do PWM ao tempo de pulso desejado
    pwm_set_gpio_level(SERVO_PIN, level);
}


// Função principal
int main() {
    stdio_init_all(); // Inicializa o sistema padrão de I/O
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Habilita o pino GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); 
    pwm_setup(slice); // Configura o PWM


    // Posição 180 graus (2400µs)
    set_servo_position(slice,  2400);
    sleep_ms(5000);
    
    // Posição 90 graus (1470µs)
    set_servo_position(slice,  1470);
    sleep_ms(5000);
    
    // Posição 0 graus (500µs)
    set_servo_position(slice,  500);
    sleep_ms(5000);



    while (true) {
        // Movimento suave entre 0 e 180 graus
        for (uint16_t pulse = 500; pulse <= 2400; pulse += 5) {
            set_servo_position(slice, pulse);
            sleep_ms(10);
        }
        for (uint16_t pulse = 2400; pulse >= 500; pulse -= 5) {
            set_servo_position(slice,  pulse);
            sleep_ms(10);
        }
    }
}
