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
    // -- Set thread <--> core --//
    CPU_ZERO(cpu_st);
    CPU_SET(*core, cpu_st);
    pthread_setaffinity_np(*thrd, sizeof(cpu_set_t), cpu_st);
}

int get_mask(cpu_set_t *cpu_st, pthread_t *thrd, int *core){
    // -- Debuging function -- //
    pthread_getaffinity_np(*thrd, sizeof(cpu_set_t), cpu_st);
    printf("THREAD %d\n",*core);
    printf("Set returned by pthread_getaffinity_np() contained:\n");
    if (CPU_ISSET(*core, cpu_st))
        printf("    CPU %d\n", *core);
}

void *latency_calculator (void *arg){
    // -- Thread function, here we calculate the latency. We use clock_nanosleep for it. -- //
    struct timespec time_sleep, time_latency;;
    time_sleep.tv_sec = 0;
    time_sleep.tv_nsec = TIME_WAIT_NS;
    long int time_thread = 0, latency = 0;

    clock_gettime(CLOCK_MONOTONIC, &time_latency);
    time_thread = (time_latency.tv_sec*1000000000) + time_latency.tv_nsec;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &time_sleep, NULL);
    clock_gettime(CLOCK_MONOTONIC, &time_latency);
    latency = (((time_latency.tv_sec*1000000000) + time_latency.tv_nsec) - time_thread) - TIME_WAIT_NS;
    *(long int*) arg = latency;
}

int main (void){
    int number_of_cores = (int) sysconf(_SC_NPROCESSORS_ONLN),  // Set number of cores of current machine
        sched_policy = SCHED_FIFO;                              // Set scheduler policy, in this case FIFO (First In First Out)
    struct sched_param param;
    struct timespec time_exe;

    param.sched_priority = 99;                                  // Initial priority value set to 99
    
    pthread_t threads[number_of_cores];
    cpu_set_t cpuset;

    // -- This is to reduce latency preset on linux systems -- //
    static int32_t latency_target_value = 0;
    int latency_target_fd = open("/dev/cpu_dma_latency", O_RDWR);
    int err = write(latency_target_fd, &latency_target_value, 4);

    long int latency[number_of_cores], 
                current_latency = 0, 
                max_latency[number_of_cores],
                avg_latency[number_of_cores];

    clock_gettime(CLOCK_MONOTONIC, &time_exe);
    double init_time = time_exe.tv_sec + ((double)time_exe.tv_nsec/1000000000),
        current_time = init_time;

    memset(latency, 0, sizeof(latency));
    memset(max_latency, 0, sizeof(max_latency));
    memset(avg_latency, 0, sizeof(avg_latency));
    int counter = 0;
    
    // -- CyclictestURJC main program, here we create n-threads (n = number of cores), that calculates latency -- //
    while((current_time-init_time) < TIME_EXE){
        for (int i = 0; i<number_of_cores; i++){
            pthread_create(&threads[i], NULL, latency_calculator, &current_latency);
            pthread_setschedparam(threads[i], sched_policy, &param);
            set_mask(&cpuset, &threads[i], &i);       
            pthread_join(threads[i], NULL);
            latency[i] = current_latency;
            avg_latency[i] = avg_latency[i] + current_latency; 
            if (counter == 0)
                max_latency[i] = current_latency;
            else {
                if (latency[i] > max_latency[i])
                    max_latency[i] = latency[i];
            }
            param.sched_priority--;
        }
        param.sched_priority = 99;
        counter++;        
        for (int core = 0; core < number_of_cores; core++){
            avg_latency[core] = avg_latency[core]/2;
            printf("[%d]\tlatencia media = %09ld ns.  |   max = %09ld ns\n",core,avg_latency[core],max_latency[core]);
        }            
        clock_gettime(CLOCK_MONOTONIC, &time_exe);
        current_time = time_exe.tv_sec + ((double)time_exe.tv_nsec/1000000000);
    }        
    return 0;
}