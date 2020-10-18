#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define STRESS_VALUE 300000000ULL

void get_time (struct timeval current, long int *s, long int *us, double *time_exec){
    // Función que devuelve los segundos y microsegundos de su llamada
    // además, devuelve el tiempo de ejecución transcurrido entre la llamada anterior
    // y la actual, SIEMPRE Y CUANDO, en la llamada anterior time_exec = 0
    gettimeofday(&current, NULL);
    *s = current.tv_sec;
    *us = current.tv_usec;
    *time_exec = *s + ((double)*us/1000000) - *time_exec;
}

void *threadfunction (void *arg){
    // Función a ejecutar en el hilo.
    for (int it = 0; it < 3; it++){
        printf("Hi from thread #%d\n", *(int *)arg);
        // Inicializaciones temporales
        struct timeval current_time;
        long int seconds, u_seconds;
        double time_exe = 0;

        /* -- TIME STAMP INIT -- */
        get_time(current_time, &seconds, &u_seconds, &time_exe);

        volatile unsigned long long i;
        for (i =0; i < STRESS_VALUE; i++);

        /* -- TIME STAMP END -- */
        get_time(current_time, &seconds, &u_seconds, &time_exe);
        
        if (time_exe > 0.9){
            printf("Violacion del ciclo de ejecución thread #%d.\t",*(int *)arg);
        }else{
            if (time_exe < 0.9)
                usleep(900000-(time_exe*1000000));                 
            printf("Thread: #%d\t", *(int *)arg);  
        }
        printf("Time: %lf\n",time_exe);      
    }
    return 0;
}

int main (void)
{
    // Creamos los id de los hilos y sus argumentos
    pthread_t thread1, thread2, thread3, thread4;
    int arg1 = 1, arg2 = 2, arg3 = 3, arg4 = 4;

    // Inicializaciones temporales
    struct timeval current_main_time;
    long int main_seconds, main_u_seconds;
    double main_time_exe = 0;

    /* -- TIME STAMP INIT -- */
    get_time(current_main_time, &main_seconds, &main_u_seconds, &main_time_exe);

    printf("Launch thread %d\n", arg1);
    pthread_create(&thread1, NULL, threadfunction, &arg1);
    printf("Launch thread %d\n", arg2);
    pthread_create(&thread2, NULL, threadfunction, &arg2);
    printf("Launch thread %d\n", arg3);
    pthread_create(&thread3, NULL, threadfunction, &arg3);
    printf("Launch thread %d\n", arg4);
    pthread_create(&thread4, NULL, threadfunction, &arg4);

    // pthread_join(thread_id, NULL) -> espera a que el hilo termine
    
    pthread_join(thread1, NULL);    
    pthread_join(thread2, NULL);    
    pthread_join(thread3, NULL);    
    pthread_join(thread4, NULL);

    /* -- TIME STAMP END -- */
    get_time(current_main_time, &main_seconds, &main_u_seconds, &main_time_exe);

    printf("Time to complete the execution: %lf\n",main_time_exe);
    printf("End program\n");
}