#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void example_pause_system(int interval, int pause_seconds, int loop_size) {
    int n_forks = 2;
    for (int i = 0; i < n_forks; i++) {
    	fork();
    }
    int pid=getpid();
    for (int i = 0; i < loop_size; i++) {
        if (i % interval == 0 && pid==getpid()) {
            printf("pause system %d/%d completed.\n", i, loop_size);
        }
        if (i == loop_size / 2){
            pause_system(pause_seconds);
        }
    }
    printf("\n");
}

void example_kill_system(int interval, int loop_size) {
    int n_forks = 2;
    for (int i = 0; i < n_forks; i++) {
    	fork();
    }
    int pid=getpid();
    for (int i = 0; i < loop_size; i++) {
        if (i % interval == 0 && pid==getpid()) {
            printf("kill system %d/%d completed.\n", i, loop_size);
        }
        if (i == loop_size / 2){
            kill_system();
        }
    }
    printf("\n");
}


int main(int argc, char** argv){
    example_pause_system(10,7,100);
    example_kill_system(10,100);
    exit(0);
}