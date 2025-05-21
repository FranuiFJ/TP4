#include "stm32f103xb.h"
#include "padsito.h"

char padsito[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void padsito_init(void) {
    // Habilitar reloj para puerto A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // PA0-PA3 -> salidas (filas)
    // PA4-PA7 -> entradas con pull-up (columnas)
    GPIOA->CRL &= ~(
        GPIO_CRL_CNF0 | GPIO_CRL_MODE0 |
        GPIO_CRL_CNF1 | GPIO_CRL_MODE1 |
        GPIO_CRL_CNF2 | GPIO_CRL_MODE2 |
        GPIO_CRL_CNF3 | GPIO_CRL_MODE3 |
        GPIO_CRL_CNF4 | GPIO_CRL_MODE4 |
        GPIO_CRL_CNF5 | GPIO_CRL_MODE5 |
        GPIO_CRL_CNF6 | GPIO_CRL_MODE6 |
        GPIO_CRL_CNF7 | GPIO_CRL_MODE7
    );

    // Filas: salida push-pull a 2MHz
    GPIOA->CRL |= GPIO_CRL_MODE0_1; // PA0
    GPIOA->CRL |= GPIO_CRL_MODE1_1; // PA1
    GPIOA->CRL |= GPIO_CRL_MODE2_1; // PA2
    GPIOA->CRL |= GPIO_CRL_MODE3_1; // PA3

    // Columnas: entrada con pull-up
    GPIOA->CRL |= GPIO_CRL_CNF4_1; // PA4
    GPIOA->CRL |= GPIO_CRL_CNF5_1; // PA5
    GPIOA->CRL |= GPIO_CRL_CNF6_1; // PA6
    GPIOA->CRL |= GPIO_CRL_CNF7_1; // PA7

    GPIOA->ODR |= 0xF0; // Pull-up en PA4-PA7
}

char padsito_getkey(void) {
    for (int i = 0; i < 4; i++) {
        GPIOA->ODR |= 0x0F;               // Desactivar todas las filas (PA0-PA3 en 1)
        GPIOA->ODR &= ~(1 << i);        // Activar solo la fila actual (poner a 0)

        for (int j = 0; j < 4; j++) {
            if (!(GPIOA->IDR & (1 << (j + 4)))) {  // Leer columna PA4-PA7
                for (volatile int d = 0; d < 5000; d++); // Antirrebote simple
                if (!(GPIOA->IDR & (1 << (j + 4)))) {
                    return padsito [i][j];
                }
            }
        }
    }
    return 0;
}