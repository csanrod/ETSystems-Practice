// APARTADO 1
// Aplicación en C multihilo que cree 4 hilos e imprima su identificador.

// APARTADO 2
// Añadir el tiempo que tarda en ejecutarse la aplicación

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// Función que devuelve los segundos y microsegundos de su llamada
// además, devuelve el tiempo de ejecución transcurrido entre la llamada anterior
// y la actual, SIEMPRE Y CUANDO, en la llamada anterior time_exec = 0
void get_time (struct timeval current, long int *s, long int *us, double *time_exec)
{
    gettimeofday(&current, NULL);
    *s = current.tv_sec;
    *us = current.tv_usec;
    *time_exec = *s + ((double)*us/1000000) - *time_exec;
}

// Función a ejecutar en el hilo. Imprime el id del thread.
void *threadfunction (void *arg)
{
    for (int it = 0; it < 3; it++){
        // Inicializaciones temporales
        struct timeval current_time;
        long int seconds, u_seconds;
        double time_exe = 0;

        // Capturamos el tiempo antes de la ejecución
        get_time(current_time, &seconds, &u_seconds, &time_exe);

        printf("Hello, I am a thread #%d.\n", *(int *)arg);
        // Código random para que tarde en ejecutarse
        volatile unsigned long long i;
        for (i =0; i < 500000000ULL; i++);
        // Fin de la ejecución del código random

        // Capturamos el tiempo DESPUES de la ejecución e imprimimos resultado
        get_time(current_time, &seconds, &u_seconds, &time_exe);

        if (time_exe > 0.9){
            printf("Violacion del ciclo de ejecución de #%d\n",*(int *)arg);
        }else{
            if (time_exe < 0.4){
                usleep(400000-(time_exe*100000));
                time_exe = 0.4;
            }        
            printf("Bye! Thread #%d with number.\n", *(int *)arg);  
        }
        printf("El tiempo transcurrido para #%d es de %lf s...\n",*(int *)arg,time_exe);
    }
    return 0;
}

int main (void)
{
    // Creamos los id de los hilos
    pthread_t thread1, thread2, thread3, thread4;
    // Creamos los argumentos para pasar a los hilos
    int arg1 = 1, arg2 = 2, arg3 = 3, arg4 = 4;
    // Inicializaciones temporales
    struct timeval current_main_time;
    long int main_seconds, main_u_seconds;
    double main_time_exe = 0;

    get_time(current_main_time, &main_seconds, &main_u_seconds, &main_time_exe);
    
    // Creamos los hilos pthread_create(a,b,c,d)
    //      a) &thread_id       -> puntero al id del hilo
    //      b) NULL             -> atributos
    //      c) threadfunction   -> función que ejecutará el hilo (puntero a void)
    //      d) NULL             -> argumentos a pasar al hilo
    //* Puntero a void es para tipo de datos genéricos...
    pthread_create(&thread1, NULL, threadfunction, &arg1);
    pthread_create(&thread2, NULL, threadfunction, &arg2);
    pthread_create(&thread3, NULL, threadfunction, &arg3);
    pthread_create(&thread4, NULL, threadfunction, &arg4);

    // pthread_join(thread_id, NULL) -> espera a que el hilo termine
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    get_time(current_main_time, &main_seconds, &main_u_seconds, &main_time_exe);
    printf("Time to complete execution: %lf\n",main_time_exe);
}