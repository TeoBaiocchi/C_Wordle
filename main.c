#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Esta funcion simplemente limpia la consola, y detecta automaticamente el 
//sistema operativo para cambiar el llamado al sistema que lo hace (multiplataforma)
void limpiarPantalla();

//Esta funcion espera que presiones enter.
//Ponerlo como buena practica luego de cada scanf mantiene
//el buffer limpio y evita problemas de ingresos cuando no queres que pasen
//Ponerlo una segunda vez con el buffer limpio es, esencialmente, 
//un "presione enter para continuar"
void bufferEnter();

//Las secciones del programa estan moduladas para un armado más sencillo
void menuPrincipal();
void nuevaPartida();
void jugada(int actual, int total);
void mensajeNroJugada(int actual, int total);

//Estas funciones setean el color del que va a salir el output. Útil para el diagrama y utilidades varias
void verde();
void rojo();
void amarillo();
void blanco();
void negro();
void colorReset();

int main(){
    menuPrincipal();
    printf("Saliste del juego. Presione enter para terminar el programa...");
    bufferEnter();
    return 0;
}

void menuPrincipal(){
    int i = 0, n, invalido = 0;
    printf("---WORDLE---\nAUS - Taller de programación I \nBaiocchi Teo, Ceron Santiago");
    printf("\n\n");
    printf("1) Jugar una partida\n");
    printf("2) Reglas del juego\n");
    printf("3) salir\n");
    char ingreso[6];
    while(i != (-1)){
        if(invalido == 1){
            printf("El numero ingresado no fue valido. Intente nuevamente... \n");
        }
        printf("Ingrese un numero para seleccionar: ");
        scanf("%d", &n);
        bufferEnter();
        switch(n){
            case 1:
                invalido = 0;
                nuevaPartida();
                break;
            case 2:
                invalido = 0;
                printf("Aca irian las reglas. Hay que acordarse de escribirlas. \n");
                printf("Presione Enter para continuar");
                bufferEnter();
                limpiarPantalla();
                menuPrincipal();
            case 3:
                return;
                break;
            default:
                limpiarPantalla();
                invalido = 1;
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
        scanf("%d", &j); 
        bufferEnter(); } while(j<1 || j>8);
        
    for(i = 0; i < j; i++){
        jugada(i+1, j);
    }
}

void jugada(int actual, int total){
    char adivinar[6] = "GATOS"; //palabra de prueba, esto hay que hacer una funcion que traiga una aleatoria de un archivo despues
    char intento[6];
    int i, j, k, comprobante = 0;
    for(i = 0; i < 5; i++){
        
        while(comprobante != 1){
            limpiarPantalla();
            mensajeNroJugada(actual, total);
            if(i == 0){
                char aux[10]; //para testear el largo
                printf("Ingrese su primer intento: ");
                scanf("%s", aux);
                bufferEnter();
                if(strlen(aux) > 5){
                    printf("Tu ingreso fue demasiado largo. Recorda que son palabras de 5 caracteres.\n");
                } else {
                    if (strlen(aux) < 5) {
                    printf("Tu ingreso fue demasiado corto. Recorda que son palabras de 5 caracteres.\n");
                    printf("Presione enter para continuar...");
                    bufferEnter();
                    } else {    
                        strcpy(intento, aux);
                        comprobante = 1;
                     }
                } 
            } 
        }
        
        //Aca el ingreso ya es valido y guardado en intento
        comprobante = 0;
        for(j = 0; j < 5; j++){
            
            if(adivinar[j] == intento[j]){
                printf("El caracter %c esta en la posicion correcta. \n", intento[j]);
            } else {
                for(k = 0; k < 5 ; k++){
                    
                    if(adivinar[k] == intento[j]){
                        printf("El caracter %c esta en la palabra, pero en otra posicion. \n", intento[j]);
                    } else comprobante++;
                    
                }
                
                printf("comprobante: %i \n", comprobante);
                if(comprobante == 4){
                    printf("El caracter %c no estaba en la palabra.", intento[j]);
                }
            }
        }
    }
}


void getWordInLine(char *fileName, int lineNumber, char *p) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fileName, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i=1;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (i==lineNumber) {
           printf("%s", line);
           strcpy(p, line);
           return;
        }
        i++;
    }
}

void mensajeNroJugada(int actual, int total){
    printf("Esta es tu jugada %i de %i \n-----\n", actual, total);
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
