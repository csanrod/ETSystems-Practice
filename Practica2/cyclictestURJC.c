#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#define TIME_EXE 60
#define TIME_WAIT_NS 1000000

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
    struct timespec time_getter;
    long int value = 0, latency = 0;
    printf(" ----------\n");
    clock_gettime(CLOCK_MONOTONIC, &time_getter);
    printf("TIME PRE nanosleep\n");
    printf("seconds: %ld\tnanoseconds: %ld\n", time_getter.tv_sec, time_getter.tv_nsec);
    value = time_getter.tv_nsec;
    clock_nanosleep(CLOCK_MONOTONIC, 0, (struct timespec *) arg, NULL);
    clock_gettime(CLOCK_MONOTONIC, &time_getter);
    printf("TIME POS nanosleep\n");
    printf("seconds: %ld\tnanoseconds: %ld\n", time_getter.tv_sec, time_getter.tv_nsec);
    value = time_getter.tv_nsec - value;
    latency = value - TIME_WAIT_NS;
    printf("\ndiff = %ld\n", value);
    printf("LATENCY = %ld\n", latency);
    printf(" ----------\n");
}

int main (void){
    int number_of_cores = (int) sysconf(_SC_NPROCESSORS_ONLN);
    
    int sched_policy = SCHED_FIFO;
    struct sched_param param;
    param.sched_priority = 99;
    
    pthread_t threads[number_of_cores];

    cpu_set_t cpuset;
    
    struct timespec nano_time;
    nano_time.tv_sec = 0;
    nano_time.tv_nsec = TIME_WAIT_NS;

    for (int i = 0; i<number_of_cores; i++){
        printf("Launch thread %d\n", i+1);
        pthread_create(&threads[i], NULL, latency_calculator, &nano_time);
        pthread_setschedparam(threads[i], sched_policy, &param);
        set_mask(&cpuset, &threads[i], &i);
        //get_mask(&cpuset, &threads[i], &i);       
        pthread_join(threads[i], NULL);
        param.sched_priority--;
    }

    return 0;
}