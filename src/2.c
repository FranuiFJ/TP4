#include "stm32f103xb.h"More actions
#include "padsito.h"
#include "stdbool.h"
#define c0 1
#define c1 2
#define c2 3
#define c3 4
#define f0 5
#define f1 6
#define f2 7
#define f3 8
int ledr=12 , ledv= 13;
int a=0, i, j;
int strcmp(const char *str1, const char *str2);
char contdf[8]={'D','1','0','8','3','0','3'};
char contrar[8];
char contranew [8];
char car; 
bool hash;
bool cambio;
int main(void) {
    _MATRIZ_PIN(c0, c1, c2, c3, f0, f1, f2, f3) ;

    while (1) {
        car= _MATRIZ_US(c0, c1, c2, c3, f0, f1, f2, f3); 
        if(cambio){
          if (car=='#'){
            contranew[a]=car;
            a++;

              if (a==8){
                contrar[8]='\0';
                strcpy(contdf,contranew);
                cambio=false;

              }
              memset(contranew, 0, sizeof(contranew));
            a=0;

          }
        }
        else if(hash){
          cambio=true;
          hash=false;
        }
        else if(car!='x'){
          contrar[a++]=car;
          if (a==8){
                contrar[8]='\0';
                 if (strcmp(contdf,contrar)==0){
                    ledv= GPIOA-> BSRR|= (1<<8);
                    hash= true;
                  }
                  else {
                    ledr= GPIOA-> BSRR|= (1<<9);
                    hash= false;
                  }
                 a=0;
                  memset(contrar, 0, sizeof(contrar));
                  
            }

        }  
    }
}