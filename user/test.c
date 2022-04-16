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

void env(int size, int interval, char* env_name) {
    int result = 1;
    int loop_size = (int)10e6;
    int n_forks = 2;
    int pid;
    for (int i = 0; i < n_forks; i++) {
        pid = fork();
    }
    for (int i = 0; i < loop_size; i++) {
        if (i % (int) (loop_size / 10e0) == 0) {
        	if (pid == 0) {
        		printf("%s %d/%d completed.\n", env_name, i, loop_size);
        	} else {
        		printf(" ");
        	}
        }
        if (i % interval == 0) {
            result = result * size;
        }
    }
    printf("\n");
}

void env_large() {
    env(10e6, 10e6, "env_large");
}

void env_freq() {
    env(10e1, 10e1, "env_freq");
}

int main(int argc, char** argv){
    env_freq();
    env_large();
    // example_pause_system(10,7,100);
    // example_kill_system(10,100);
    exit(0);
}
