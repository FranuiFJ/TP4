#include "padsito.h"

int main(void) {
    padsito_init();

    while (1) {
        char key = padsito_getkey();
        if (key) {
            //auratalk
        }
    }
}