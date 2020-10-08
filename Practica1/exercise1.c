// APARTADO 1
// Aplicación en C multihilo que cree 4 hilos e imprima su identificador.

#include <pthread.h>
#include <stdio.h>
#include <string.h>

// Función a ejecutar en el hilo. Imprime el id del thread.
void *threadfunction (void *arg)
{
    printf("Hello, I am a thread #%d.\n", *(int *)arg);
    // Código random para que tarde en ejecutarse
    volatile unsigned long long i;
    for (i =0; i < 1000000000ULL; i++);
    // Fin de la ejecución del código random
    printf("Bye! Thread #%d with number.\n", *(int *)arg);
    return 0;
}

int main (void)
{
    // Creamos los id de los hilos
    pthread_t thread1, thread2, thread3, thread4;
    // Creamos los argumentos para pasar a los hilos
    int arg1 = 1, arg2 = 2, arg3 = 3, arg4 = 4;
    
    // Creamos los hilos pthread_create(a,b,c,d)
    //      a) &thread_id -> puntero al id del hilo
    //      b) NULL -> atributos
    //      c) threadfunction -> función que ejecutará el hilo
    //      d) NULL -> argumentos a pasar al hilo
    pthread_create(&thread1, NULL, threadfunction, &arg1);
    pthread_create(&thread2, NULL, threadfunction, &arg2);
    pthread_create(&thread3, NULL, threadfunction, &arg3);
    pthread_create(&thread4, NULL, threadfunction, &arg4);

    // pthread_join(thread_id, NULL) -> espera a que el hilo termine
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);    
}