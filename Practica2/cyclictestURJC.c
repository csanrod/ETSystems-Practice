#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define TIME_EXE 60

void set_mask(cpu_set_t *cpu_st, pthread_t *thrd, int *core){
    CPU_ZERO(cpu_st);
    CPU_SET(*core, cpu_st);
    pthread_setaffinity_np(*thrd, sizeof(cpu_set_t), cpu_st);
}

int get_mask(cpu_set_t *cpu_st, pthread_t *thrd, int *core){
    pthread_getaffinity_np(*thrd, sizeof(cpu_set_t), cpu_st);
    printf("THREAD %d\n",*core);
    printf("Set returned by pthread_getaffinity_np() contained:\n");
    if (CPU_ISSET(*core, cpu_st))
        printf("    CPU %d\n", *core);
}

void *latency_calculator (void *arg){
    printf(" ... inside thread #%d ...\n", *(int*)arg+1);
}

int main (void){
    int number_of_cores = (int) sysconf(_SC_NPROCESSORS_ONLN);
    int sched_policy = SCHED_FIFO;
    struct sched_param param;
    param.sched_priority = 99;
    pthread_t threads[number_of_cores];
    cpu_set_t cpuset;

    for (int i = 0; i<number_of_cores; i++){
        printf("Launch thread %d\n", i+1);
        pthread_create(&threads[i], NULL, latency_calculator, &i);
        pthread_setschedparam(threads[i], sched_policy, &param);
        set_mask(&cpuset, &threads[i], &i);
        //get_mask(&cpuset, &threads[i], &i);       
        //pthread_join(threads[i], NULL);
        param.sched_priority--;
    }

    return 0;
}