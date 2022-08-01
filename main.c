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
    printf("3) Salir\n");
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
    int i, j, j2, salir = 0, n;
    do{
        limpiarPantalla();
        printf("Ingrese cuantas palabras para adivinar en esta partida (No mayor a 8): ");
        scanf("%d", &j);
        bufferEnter();} while(j<1 || j>8);
        j2 = j;

    for(i = 0; i <= j; i++)
    {
        if(i != 0  && i != j)
        {
            printf("Terminaste tu partida %i de %i, para terminar el juego ahora ingrese 0\nPara continuar, ingrese cualquier otra tecla: ", i, j);
            scanf("%d", &n);
            bufferEnter();
            if(n == 0)
            {
                j2 = i; //Si se corta la partida antes de tiempo, en J2 se guarda cuantas jugadas se jugaron efectivamente
                salir = 1;
            }
        }



        if(i == j || salir == 1) //Cuando la partida termina, ya sea por que termino o porque fue cortada
        {
            printf("Presione enter para continuar.\n");
            bufferEnter();
            limpiarPantalla();
            printf("Fin del juego...\n");
            printf("El promedio de tus puntajes fue de: \n");
            printf("Si deseas revisar el mapa o puntaje de una jugada especifica de tus %i jugadas, ingresala. \nCaso contrario, ingresa 0 para volver al menu: ", j2);
            scanf("%d", &n);
            bufferEnter();
        } else {
            jugada(i+1, j);
        }
    }
}

void jugada(int actual, int total){
    char wordle[6] = "GATOS"; //palabra de prueba, esto hay que hacer una funcion que traiga una aleatoria de un archivo despues
    char intento[6];
    int i, j, k, l, comprobante = 0, puntaje = 5000;

    //array de verificacion de "estado de la letra" para asignar puntaje
    //5 espacios, uno por cada letra a adivinar
    // valor "0", no fue encontrada. "1", fue adivinada pero en el lugar incorrecto, "2", letra ya validad en su posicion
    int punt[5] = {0, 0, 0, 0, 0};

    char palabras[7][6]={{'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}, {'\0'}};

    limpiarPantalla();
    mensajeNroJugada(actual, total);

    for(i = 0; i < 6; i++)
    {
        if(i>0)
        {
            //Restar 500 puntos cada vez que se hace un nuevo intento, excepto en el primer intento
            puntaje = puntaje - 500;
        }
        printf("\nTu puntaje es de %d puntos\n", puntaje);

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



        j = 0;  //Normaliza la palabra a mayuscula
        while(intento[j])
        {
            intento[j] = toupper(intento[j]);
            j++;
        }

        //guardar los intentos para mostrarlos al final de la sesion
        for(k=0; k<5; k++)
        {
            palabras[i][k]=intento[k];
        }
        palabras[i][6] = '\0';


        //Si la palabra y el ingreso son iguales, ganaste!
        //Break para salir del for de los 5 intentos de ingresar palabra y cortar las otras verificaciones
        if (strcmp(intento, wordle) == 0)
        {
            if(i == 0)
            {
                puntaje = puntaje + 5000;
            } else
            {
                puntaje = puntaje + 2000;
            }
            verde();
            printf("Adivinaste la palabra!\n");
            printf("Tu puntaje final es de %d puntos.\n", puntaje);
            colorReset();
            break;
        }



        //Aca el ingreso ya es valido y guardado en intento
        //Se revisa en las 5 letras del intento si esta bien puesta,
        //o si esta en cualquier otro lado de la palabra (con un for anidado)
        for(j = 0; j < 5; j++)
        {
            comprobante = 0;

            if(wordle[j] == intento[j])
            { //letra correcta en lugar correcto
                verde();
                printf("%c", intento[j]);
                if(punt[j] != 2)
                {  //controlo que la letra no haya sumado puntos todavia
                puntaje = puntaje + 100;
                punt[j] = 2;
                }

            } else {
                for(k = 0; k < 5 ; k++)
                {   //letra correcta en lugar incorrecto
                    if(wordle[k] == intento[j])
                    {
                        negro();
                        printf("%c", intento[j]);

                        if(punt[k] == 0)
                        {
                            puntaje = puntaje + 50;
                            punt[k] = 1;
                        }
                        k = 6; //Para cortar antes este for si se diere el caso
                    } else comprobante++;
                }

                if(comprobante == 5)
                { //la letra no esta en la palabra
                    rojo();
                    printf("%c", intento[j]);
                }
            }
        }
        colorReset();
    }

    //aca termina el for de cada intento
    /*muestro las palabras usadas en cada intento de la ultima jugada
      printf("Intentos realizados en la ultima jugada: \n");
      for(i=0; i<5; i++)
        {
            for(k=0; k<6; k++)
            {
                printf("%c", palabras[i][k]);
            }
            printf("\n");
        }*/
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
