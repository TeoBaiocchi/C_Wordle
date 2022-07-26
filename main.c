#include <stdio.h>
#include <stdlib.h>


//Esta funcion simplemente limpia la consola, y detecta automaticamente el 
//sistema operativo para cambiar el llamado al sistema que lo hace (multiplataforma)
void limpiarPantalla();

//Funcion "presione enter para continuar" / tambien limpia el buffer 
//puede ser util en algunos casos de ingreso de strings 
// (Revisar)
void bufferEnter();

//Las secciones del programa estan moduladas para un armado más sencillo
void menuPrincipal();
void nuevaPartida();
void jugada(int actual, int total);

//Estas funciones setean el color del que va a salir el output. Útil para el diagrama y utilidades varias
void verde();
void rojo();
void amarillo();
void blanco();
void negro();
void colorReset();

int main(){
    menuPrincipal();
    printf("Saliste del juego. Presione enter para terminar el programa");
    bufferEnter();
    bufferEnter();
    //Fijate que esto lo pongo para mostrarte que es lo que hace el bufferEnter
    //El tema es que antes andaba de una, ahora lo tengo que poner 2 veces. No sé
    return 0;
}

void menuPrincipal(){
    int i = 0, n;
    printf("---WORDLE---\nAUS - Taller de programación I \nBaiocchi Teo, Cerón Santiago");
    printf("\n\n");
    printf("1) Jugar una partida\n");
    printf("2) salir\n");
    char ingreso[6];
    while(i != (-1)){
        printf("Ingrese un numero para seleccionar: ");
        scanf("%d", &n);
        switch(n){
            case 1:
                nuevaPartida();
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

void nuevaPartida(){
    int i, j;
    do{
        limpiarPantalla();
        printf("Ingrese una cantidad de partidas para jugar (No mayor a 8): ");
        scanf("%d", &j); } while(j<1 || j>8);
        
    for(i = 0; i < j; i++){
        jugada(i+1, j);
    }
}

void jugada(int actual, int total){
    printf("Esta es tu jugada %i de %i \n", actual, total);
}

void verde(){
    printf("\033[0;32m");
}

void rojo(){
    //Setea el color a rojo
    printf("\033[0;31m");
}

void amarillo(){
    printf("\033[0;33m");
}

void blanco(){
    printf("\033[0;37m");
}
void negro(){
    printf("\033[1;30m");
}

void colorReset(){
    //vuelve al color default
    printf("\033[0m");
}


void limpiarPantalla(){
  #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
 }


void bufferEnter(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF){} 
}