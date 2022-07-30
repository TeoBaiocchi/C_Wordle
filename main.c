#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



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
    printf("---WORDLE---\nAUS - Taller de programacion I \nBaiocchi Teo, Ceron Santiago");
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
                limpiarPantalla();
                menuPrincipal();
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
        //char todosIntentos[j][26][3];
    for(i = 0; i < j; i++){
        jugada(i+1, j);
        if(i+1 == j)
        {
            printf("Fin del juego...\n");
            printf("Tu puntaje total fue de: \n");
            printf("Si deseas revisar el mapa de una jugada de tus %i jugadas, en particular, ingresala. \nSino, ingresa 0 para salir del programa: ", j);
            bufferEnter();
        }
    }
}

void jugada(int actual, int total){
    char adivinar[6] = "GATOS"; //palabra de prueba, esto hay que hacer una funcion que traiga una aleatoria de un archivo despues
    char intento[6];
     //Para guardar
    int i, j, k, l, comprobante = 0, puntaje=5000, punt[5];

    limpiarPantalla();
    mensajeNroJugada(actual, total);

    //Array entero que va a servir para que una letra correcta no sume puntos mas de una vez
    for(l=0; l<5; l++){
        punt[l]=0;
    }


    for(i = 0; i < 6; i++)
    {
        //Restar 500 puntos cada vez que se hace un nuevo intento, excepto en el primer intento
        if(i>0){
            puntaje=puntaje-500;
        }

        printf("\n\nTu puntaje es de %d puntos\n\n", puntaje);

        comprobante = 0;
        while(comprobante != 1)
        {

                char aux[10]; //para testear el largo

                printf("Ingrese su intento N°%i: ", i+1);
                scanf("%s", aux);
                bufferEnter();

                if(strlen(aux) > 5)
                {
                    printf("Tu ingreso fue demasiado largo. Recorda que son palabras de 5 caracteres.\n");
                    printf("Presione enter para continuar...");
                    bufferEnter();
                } else {
                    if (strlen(aux) < 5)
                    {
                    printf("Tu ingreso fue demasiado corto. Recorda que son palabras de 5 caracteres.\n");
                    printf("Presione enter para continuar...");
                    bufferEnter();
                    } else {
                        strcpy(intento, aux);
                        comprobante = 1;
                    }
                }
        }


        //Normaliza la palabra a mayuscula
        j = 0;
        while(intento[j])
        {
            intento[j] = toupper(intento[j]);
            j++;
        }


        //Si la palabra y el ingreso son iguales, ganaste!
        //Break para salir del for de los 5 intentos de ingresar palabra y cortar las otras verificaciones
        if (strcmp(intento, adivinar) == 0)
        {
            if(i=0){
                puntaje=puntaje+5000;
            } else{
                puntaje=puntaje+2000;
            }
            verde();
            printf("Adivinaste la palabra!\n");
            printf("Tu puntaje final es de %d puntos", puntaje);
            colorReset();
            break;
        }



        //Aca el ingreso ya es valido y guardado en intento
        //Se revisa en las 5 letras del intento si esta bien puesta,
        //o si esta en cualquier otro lado de la palabra (con un for anidado)
        for(j = 0; j < 5; j++)
        {
            comprobante = 0;

            //letra correcta en lugar correcto
            if(adivinar[j] == intento[j])
            {
                verde();
                printf("%c", intento[j]);

                //controlo que la letra no haya sumado puntos todavia
                if(punt[j]==0){

                puntaje=puntaje+100;
                punt[j]=1;

                }

            } else {
                for(k = 0; k < 5 ; k++)
                {   //letra correcta en lugar incorrecto
                    if(adivinar[k] == intento[j])
                    {
                        negro();
                        printf("%c", intento[j]);
                        puntaje=puntaje+50;
                        k=6; //Para cortar antes este for si se diere el caso
                    } else comprobante++;
                }
                //la letra no esta en la palabra
                if(comprobante == 5)
                {
                    rojo();
                    printf("%c", intento[j]);
                }
            }
        }

        colorReset();
    } //aca termina el for de cada intento

    printf("Presione enter para continuar. ");
    bufferEnter();
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
    printf("Esta es tu jugada %i de %i \nRecorda que Verde = Lugar correcto, Gris = Lugar incorrecto, Rojo = Letra incorrecta \n-----\n", actual, total);
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
