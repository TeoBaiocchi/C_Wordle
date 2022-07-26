#include <stdio.h>
#include <stdlib.h>


//Esta funcion simplemente limpia la consola, tanto en windows como en linux
void limpiarPantalla();

//Esta funcion supuestamente limpia el buffer. No te voy a mentir, no recuerdo como funciona o por qué hacia falta
//Pero puede usarse como un "presiona enter para continuar"
void bufferEnter();

//Esta bueno ir seccionando estas cosas en lugar de tener todo en el main
void menuPrincipal();

int main(){
    menuPrincipal();
    return 0;
}

void menuPrincipal(){
    int i = 0, n;
    printf("---WORDLE---\nAUS - Taller de programación I \nBaiocchi Teo, Ceron Santiago");
    printf("\n\n");
    printf("1) Jugar una partida\n");
    printf("2) salir\n");
    
    while(i != (-1)){
        printf("Ingrese un numero para seleccionar: ");
        scanf("%d", &n);

        switch(n){
            case 1:
                //No hay nada hecho jaja
                limpiarPantalla();
                break;
            
            case 2:
                return;
                break;
            
            default:
                limpiarPantalla();
                printf("Ingrese una opción valida. \n");
                menuPrincipal();
                break;
        }

    }
}

void limpiarPantalla(){
  #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
  //Esta funcion la hicimos de esta manera en su momento porque
  //el comando para limpiar la consola es distinto segun el sistema operativo
  
  //Pero además de eso no puede hacerse pidiendote el sistema y despues con un "if"
  //porque aunque nunca ejecutes esa linea, por estar escrita ya vas a tener un error en el programa
  
  //Basicamente, definiendola de esta forma funciona bien y es automatico
 }

void bufferEnter(){
  //fflush(stdin); 
  //Tengo que revisar esta funcion, anda raro
  int c;
  while ((c = getchar()) != '\n' && c != EOF){} 
}
