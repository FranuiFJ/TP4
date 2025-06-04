#include "padsito.h"
#include "stm32f103xb.h"
#include <string.h>

int main(void) {
    TecladoMatri_init();
        while (1) {
            char tecla = TecladoMatri();
            if (tecla) {
                
            }
        }
}