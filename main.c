#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define CANTIDAD_PALABRAS 30


//Las secciones del programa estan moduladas para un armado más sencillo
void menuPrincipal();
void nuevaPartida();
int jugada(int actual, int total, char todosIntentos[][7][6], char todosWordles[][1][6]);
void wordleRandomizer(char wordle[]);
void mensajeNroJugada(int actual, int total);
void mostrarJugada(char todosIntentos[][7][6], char todosWordles[][1][6], int nroJugada, int puntaje);

//Estas funciones setean el color del que va a salir el output. Útil para el diagrama y utilidades varias
void verde();
void rojo();
void amarillo();
void blanco();
void negro();
void colorReset();

//Esta funcion simplemente limpia la consola, y detecta automaticamente el
//sistema operativo para cambiar el llamado al sistema que lo hace (multiplataforma)
void limpiarPantalla();


//Esta funcion limpia el buffer luego de cada ingreso
//Ya que queda a la espera de que presiones enter
//Hace las veces de fflush, en cierta forma
//Y además, puede usarse como "Presione enter para continuar"
void bufferEnter();

//funcion dada en comunidades para acceder a un archivo
//La usamos con un path relativo, "palabras.txt" *tiene que* estar
//en la misma carpeta que "main.c"
void getWordInLine(char *fileName, int lineNumber, char *p);


int main(){

    menuPrincipal();
    printf("Saliste del juego. Presione enter para terminar el programa...");
    bufferEnter();
    return 0;
}


void menuPrincipal(){

    int n, invalido = 0, salirMenu = 0;


    while(salirMenu == 0)
    {
        printf("---WORDLE---\nAUS - Taller de programacion I \nBaiocchi Teo, Ceron Santiago");
        printf("\n\n");
        printf("1) Jugar una partida\n");
        printf("2) Reglas del juego\n");
        printf("3) Salir\n");

        if(invalido == 1)
        {
            printf("El numero ingresado no fue valido. Intente nuevamente... \n");
        }

        printf("Ingrese un numero para seleccionar: ");
        scanf("%d", &n);
        bufferEnter();

        switch(n)
        {
            case 1:
                invalido = 0;
                nuevaPartida();
                limpiarPantalla();
                break;

            case 2:
                invalido = 0;
                verde(); printf("Wordle! "); amarillo(); printf("El juego de adivinar una palabra sin ninguna pista en solo 6 intentos!\n");
                colorReset(); printf("-----\n");
                printf("El juego consiste en el ingreso de palabras de 5 caracteres, despues de cada ingreso\n");
                printf("se te indicara con colores que letras dentro de tu ingreso correspondian de cierta manera con una palabra misteriosa");
                negro(); printf(" (el wordle!)\n"); colorReset();
                verde(); printf("Verde indica que la letra esta en la posicion correcta\n");
                colorReset(); printf("Estas letras bien adivinadas sumaran 100 puntos por unica vez cuando acertadas.\n");
                amarillo(); printf("Amarillo indica que la letra es parte de la palabra misteriosa, pero no en esa posicion\n");
                colorReset(); printf("Estas letras sumaran 50 puntos por unica vez cuando acertadas\n");
                negro(); printf("Gris indica que la letra es completamente desacertada. Ningun punto para vos.\n");
                colorReset();
                rojo();
                printf("\nEntendiste?\n");
                negro(); printf("(Ingresa tu respuesta): ");
                rojo();
                bufferEnter();
                limpiarPantalla();
                printf("Barbaro. Suerte!");
                colorReset();
                break;

            case 3:
                salirMenu = 1;
                break;

            default:
                limpiarPantalla();
                invalido = 1;
                break;
        }
    }
}



void nuevaPartida(){

    int i, j, k, j2, salir = 0, n, max = 0, min = 10001, imax = 0, imin = 0, p = 0;
    int todosPuntajes[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    //Todos puntajes tiene lugar para guardar los puntajes de las 8 partidas
    //Si es que se fueran a jugar las 8. Es inicializado en -1 para poder tener control
    //de cuantas se jugaron, a fin de poder calcular los minimos, maximos y promedio.

    float sum = 0, prom = 0;

    char todosIntentos[9][7][6];
    char todosWordles[9][1][6];
    //Estos arrays van a contener los strings de los intentos y las palabras magicas de todas las partidas que se jueguen
    //La primera dimensión corresponde al numero de jugada, la segunda a una palabra, y la tercera a los caracteres individuales


    do{
        limpiarPantalla();
        printf("Ingrese cuantas palabras para adivinar en esta partida (No mayor a 8): ");
        scanf("%d", &j);
        bufferEnter();} while(j<1 || j>8);

    j2 = j;


    for(i = 0; i <= j; i++)
    {   //Este for va a ser la sesion de juego.


        if(i != 0  && i != j) //Si la jugada NO es ni la primera ni la ultima
        {   //se pregunta al usuario si quiere abandonar la partida
            printf("Terminaste tu partida %i de %i, si desea terminar el juego ahora mismo ingrese 0\nPara continuar, ingrese cualquier otra cosa y presione enter: ", i, j);
            scanf("%d", &n);
            bufferEnter();
            if(n == 0)
            {
                j2 = i; //Si se corta la partida antes de tiempo, en J2 se guarda cuantas jugadas se jugaron efectivamente
                salir = 1;
            }
        }

        if(i == j || salir == 1)
        {   //Cuando la partida termina, ya sea por que termino o porque fue cortada
            //Dentro de este if, se genera toda la pantalla de fin del juego y se
            //llama a las funciones correspondientes

            while(1)
            {   //"While" porque se debe poder revisualizar
                //esta pantalla hasta que se decida volver al menu
                printf("Presiona enter para continuar...");
                bufferEnter();
                limpiarPantalla();
                negro();
                printf("Fin del juego...\n");
                colorReset();

                //puntaje maximo
                for(k=0; k<8; k++)
                {
                    if(todosPuntajes[k] > max && todosPuntajes[k] != -1)
                    {
                        max = todosPuntajes[k];
                        imax = k + 1;
                    }
                }


                //puntaje minimo
                for(k=0; k<8; k++)
                {
                    if(todosPuntajes[k] < min && todosPuntajes[k] != -1)
                    {
                        min = todosPuntajes[k];
                        imin = k + 1;
                    }
                }

                //promedio
                for(k=0; k<8; k++)
                {
                    if(todosPuntajes[k] != 0 && todosPuntajes[k] != -1)
                    {
                        sum = sum + todosPuntajes[k];
                        p++;
                    }
                }
                if(p != 0)
                {
                     prom = sum / p;
                } else {
                    prom = 0.00;
                }


                verde();
                printf("Tu puntaje maximo fue de %d puntos y lo obtuviste en la partida %d\n", max, imax);
                rojo();
                printf("Tu puntaje minimo fue de %d puntos y lo obtuviste en la partida %d\n", min, imin);
                amarillo();
                printf("El promedio de los puntajes en que lograste una victoria fue de: %.2f puntos\n", prom);
                colorReset();
                printf("Si deseas revisar el mapa o puntaje de una jugada especifica de tus %i jugadas, ingresala. \nCaso contrario, ingresa 0 para volver al menu: ", j2);

                scanf("%d", &n);
                bufferEnter();
                //Sale del juego
                if(n == 0)
                {
                    salir = 2; //para salir del for padre
                    break;
                }

                n = n-1;
                if(n<j2 && n>=0)
                {
                    mostrarJugada(todosIntentos, todosWordles, n, todosPuntajes[n]);
                }
            }
            if(salir == 2)
            {
                break; //Si se entro al fin de juego y se salio al menu, se termina la sesion.
            }
        } else {
            todosPuntajes[i] = jugada(i, j, todosIntentos, todosWordles);

            //si *no* termino la partida, se efectua la jugada.
            //La jugada recibe los array para almacenar los string pertinentes
            //y devuelve el puntaje de la ronda.
        }

    }
}




int jugada(int actual, int total, char palabras[][7][6], char todosWordles[][1][6]){

    char wordle[6];
    char intento[6];
    int i, j, k, l, comprobante = 0, puntaje = 5000, derrota = 0;


    int punt[5] = {0, 0, 0, 0, 0};
    //array de verificacion de "estado de la letra" para asignar puntajes
    //5 espacios, uno por cada letra a adivinar. Funciona por posición
    // valor "0", no fue encontrada. "1", fue adivinada pero en el lugar incorrecto, "2", letra ya validada en su posicion

    limpiarPantalla();
    mensajeNroJugada(actual + 1, total);
    wordleRandomizer(wordle); //Toma una palabra aleatoria del archivo palabras.txt y la guarda en wordle


    //Guardamos el wordle de la ronda en el registro para utilizar mas tarde
    strcpy(todosWordles[actual][0], wordle);


    for(i = 0; i < 6; i++)
    {   //6 = cantidad de intentos permitidos

        if(i>0)
        {
            //Restar 500 puntos cada vez que se hace un nuevo intento, excepto en el primer intento
            puntaje = puntaje - 500;
        }

        printf("\nTu puntaje es de %d puntos\n", puntaje);

        comprobante = 0;
        while(comprobante != 1) //Comprobacion de ingreso valido
        {
                char aux[10];
                printf("Ingrese su intento Nro %i: ", i+1);
                scanf("%s", aux);
                bufferEnter();

                if(strlen(aux) > 5)
                {
                    printf("Tu ingreso fue demasiado largo. Recorda que son palabras de 5 caracteres.\n");
                } else {
                    if (strlen(aux) < 5)
                    {
                    printf("Tu ingreso fue demasiado corto. Recorda que son palabras de 5 caracteres.\n");
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



        //Símil que "todosWordles". Guardamos los intentos de la sesion para uso posterior
        strcpy(palabras[actual][i], intento);
        palabras[actual][i+1][0] = 'a';
        //La palabra siguiente queda "inhabilitada", hasta que se use en la proxima iteracion
        //Se chequea luego por este caracter de verificacion en mostrarJugada
        //(nota: un intento valido esta normalizado a mayusculas y nunca va a empezar por 'a')



        if (strcmp(intento, wordle) == 0)
        {
           //Si la palabra y el ingreso son iguales, ganaste!
           //Break para salir del for de los 5 intentos de ingresar palabra y cortar las otras verificaciones
            if(i == 0)
            {
                puntaje = puntaje + 5000; //Suma de puntos caso de adivinar en primer intento
            } else
            {
                puntaje = puntaje + 2000;
            }
            verde();
            printf("Adivinaste la palabra!\n");
            printf("Tu puntaje final es de %d puntos.\n", puntaje);
            colorReset();
            break;
        } else {
            derrota++; //Contador de todas las veces que *no* se adivino una palabra
        }


        for(j = 0; j < 5; j++)
        {
            //Se revisa en las 5 letras del intento si esta bien puesta,
            //o si esta en cualquier otro lado de la palabra (con un for anidado)
            //(A esta altura se tiene un ingreso validado que NO es el wordle, para analizar)
            comprobante = 0;
            if(wordle[j] == intento[j])
            { //letra correcta en lugar correcto
                verde();
                printf("%c", intento[j]);
                if(punt[j] != 2)
                {  //control que la letra no haya sumado puntos todavia
                puntaje = puntaje + 100;
                punt[j] = 2;
                }

            } else {
                for(k = 0; k < 5 ; k++)
                {   //letra correcta en lugar incorrecto
                    if(wordle[k] == intento[j])
                    {
                        amarillo();
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
                    negro();
                    printf("%c", intento[j]);
                }
            }
        }
        colorReset();
        if(derrota == 6) //No se logro adivinar la palabra luego de 6 intentos.
        {
            puntaje = 0;
            rojo();
            printf("\n\nPerdiste! Te quedaste sin intentos para adivinar la palabra\n");
            colorReset();
            printf("Tu puntaje final es: %d puntos\n", puntaje);
            printf("El Wordle era: ");
            verde();
            printf("%s\n", wordle);
            colorReset();
        }
    }

    return puntaje;
}




void mostrarJugada(char todosIntentos[][7][6], char todosWordles[][1][6], int nroJugada, int puntaje){
    int i, j, k, comprobante;
    char wordle[6];
    char intento[6];

    strcpy(wordle, todosWordles[nroJugada][0]);
    wordle[5] = '\0';
    //Copiamos el wordle de la partida especificada
    //en una variable para poder reconstruir el mapa comparando contra ella

    limpiarPantalla();
    rojo();
    printf("Estadisticas de tu jugada Nro %i", nroJugada+1); colorReset(); printf("\n------------------\n");
    printf("Tu puntaje en esta ronda fue de: "); verde(); printf("%i\n", puntaje); colorReset();
    printf("Tu Wordle era: "); verde(); printf("%s\n\n", wordle); colorReset();
    printf("Y el mapeo de tus intentos se ve...\nAsi:\n-----\n");


    for(i = 0; i < 6; i++) // 6 palabras... maximo
    {
        colorReset();
        if(todosIntentos[nroJugada][i][0] != 'a')
            {
                strcpy(intento, todosIntentos[nroJugada][i]);
            } //Si no hay un string en este nro de intento, (porque se logro en menos),
        else{ //corta el mapa.
            break;
        }


        for(j = 0; j < 5; j++)
        {   //Reciclamos la funcion de "jugada", sin los elementos de puntaje
            comprobante = 0;
            if(wordle[j] == intento[j])
            {
                verde(); //letra correcta
                printf("%c", intento[j]);
            } else {
                for(k = 0; k < 5 ; k++)
                {   //letra correcta en lugar incorrecto
                    if(wordle[k] == intento[j])
                    {
                        amarillo();
                        printf("%c", intento[j]);
                    } else comprobante++;
                }

                if(comprobante == 5)
                { //la letra no esta en la palabra
                    negro();
                    printf("%c", intento[j]);
                }
            }
        }
    printf("\n");
    }
    colorReset();
}




void wordleRandomizer(char wordle[]){

    //Se randomiza la semilla
    srand(time(NULL));

    //n = entero entre 0 y 30, la cantidad de palabras definida en el archivo dado
    int n = (rand() % CANTIDAD_PALABRAS);

    if(n == 0)
    {
        n++;
    }

    getWordInLine("palabras.txt", n, wordle);
    wordle[5] = '\0';

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
    printf("Esta es tu jugada %i de %i \nRecorda que...\nVerde = Lugar correcto, Amarillo = Lugar incorrecto, Gris = Letra incorrecta\nCada letra en el wordle es unica y no va a repetirse \n-----\n", actual, total);
}


void verde(){
    printf("\033[1;32m");
}

void rojo(){
    //Setea el color a rojo
    printf("\033[1;31m");
}

void amarillo(){
    printf("\033[1;33m");
}

void blanco(){
    printf("\033[1;37m");
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
