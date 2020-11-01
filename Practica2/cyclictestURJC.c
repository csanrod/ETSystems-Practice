#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

    struct timespec time_sleep;
    time_sleep.tv_sec = 0;
    time_sleep.tv_nsec = TIME_WAIT_NS;

    struct timespec time_latency;
    long int time_thread = 0, latency = 0;
    //printf(" ----------\n");
    clock_gettime(CLOCK_MONOTONIC, &time_latency);
    //printf("TIME PRE nanosleep\n");
    //printf("seconds: %ld\tnanoseconds: %ld\n", time_latency.tv_sec, time_latency.tv_nsec);
    time_thread = (time_latency.tv_sec*1000000000) + time_latency.tv_nsec;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &time_sleep, NULL);
    clock_gettime(CLOCK_MONOTONIC, &time_latency);
    //printf("TIME POS nanosleep\n");
    //printf("seconds: %ld\tnanoseconds: %ld\n", time_latency.tv_sec, time_latency.tv_nsec);
    
    latency = (((time_latency.tv_sec*1000000000) + time_latency.tv_nsec) - time_thread) - TIME_WAIT_NS;
    //printf("\ndiff = %ld\n", time_thread);
    //printf("LATENCY = %ld\n", latency);
    //printf(" ----------\n");
    *(long int*) arg = latency;
}

int main (void){
    int number_of_cores = (int) sysconf(_SC_NPROCESSORS_ONLN);
    
    int sched_policy = SCHED_FIFO;
    struct sched_param param;
    param.sched_priority = 99;

    struct timespec time_exe;
    clock_gettime(CLOCK_MONOTONIC, &time_exe);
    double init_time = time_exe.tv_sec + ((double)time_exe.tv_nsec/1000000000);
    double current_time = init_time;
    //printf("TIME:%lf\n",init_time);
    
    pthread_t threads[number_of_cores];

    cpu_set_t cpuset;

    static int32_t latency_target_value = 0;
    int latency_target_fd = open("/dev/cpu_dma_latency", O_RDWR);
    int err = write(latency_target_fd, &latency_target_value, 4);

    long int latency[number_of_cores], 
                current_latency = 0, 
                max_latency[number_of_cores],
                avg_latency[number_of_cores];
    memset(latency, 0, sizeof(latency));
    memset(max_latency, 0, sizeof(max_latency));
    memset(avg_latency, 0, sizeof(avg_latency));
    int couter = 0;
    
    while((current_time-init_time) < TIME_EXE){
        for (int i = 0; i<number_of_cores; i++){
            //printf("Launch thread %d\n", i+1);
            pthread_create(&threads[i], NULL, latency_calculator, &current_latency);
            pthread_setschedparam(threads[i], sched_policy, &param);
            set_mask(&cpuset, &threads[i], &i);
            //get_mask(&cpuset, &threads[i], &i);       
            pthread_join(threads[i], NULL);
            latency[i] = current_latency;
            avg_latency[i] = avg_latency[i] + current_latency; 
            if (couter == 0)
                max_latency[i] = current_latency;
            else {
                if (latency[i] > max_latency[i])
                    max_latency[i] = latency[i];
            }
            param.sched_priority--;
        }
        param.sched_priority = 99;
        couter++;
        
        for (int core = 0; core < number_of_cores; core++){
            avg_latency[core] = avg_latency[core]/2;
            printf("[%d]\tlatencia media = %09ld ns.  |   max = %09ld ns\n",core,avg_latency[core],max_latency[core]);
        }
            
        clock_gettime(CLOCK_MONOTONIC, &time_exe);
        current_time = time_exe.tv_sec + ((double)time_exe.tv_nsec/1000000000);
    }  
        
    return 0;
}