#include "stm32f103xb.h"
#include "padsito.h"

char matrix[4][4] = {
                        {'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','#','D'}
                        };

void TecladoMatri_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

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
    GPIOA->CRL |= GPIO_CRL_MODE0_1; 
    GPIOA->CRL |= GPIO_CRL_MODE1_1; 
    GPIOA->CRL |= GPIO_CRL_MODE2_1; 
    GPIOA->CRL |= GPIO_CRL_MODE3_1; 
    GPIOA->CRL |= GPIO_CRL_CNF4_1; 
    GPIOA->CRL |= GPIO_CRL_CNF5_1; 
    GPIOA->CRL |= GPIO_CRL_CNF6_1; 
    GPIOA->CRL |= GPIO_CRL_CNF7_1; 
    GPIOA->ODR |= 0xF0; 
}

char TecladoMatri(void) {
    for (int quiere = 0; quiere < 4; quiere++) {
        GPIOA->ODR |= 0x0F;               
        GPIOA->ODR &= ~(1 << quiere);        

        for (int bija = 0; bija < 4; bija++) {
            if (!(GPIOA->IDR & (1 << (bija + 4)))) { 
                for (volatile int f = 0; f < 5000; f++);
                    if (!(GPIOA->IDR & (1 << (bija + 4)))) {
                        return matrix[quiere][bija];
                }
            }
        }
    }
    return 0;
}