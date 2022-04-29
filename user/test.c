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
    printf("Stats of %d\n",getpid());
    print_stats();
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
        if (i % (int)(loop_size / 10e0) == 0) {
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
    printf("Stats of %s\n", env_name);
    print_stats();
}

void env_large() {
    env(10e6, 10e6, "env_large");
}

void env_freq() {
    env(10e1, 10e1, "env_freq");
}


void mytest() {
    int n_forks = 2;
    int pid;
    int status;
    int main_pid = getpid();
    for (int i = 0; i < n_forks; i++) {
    	pid = fork();
    }
    if (pid != 0) {
        wait(&status);
        printf("My Son Died: %d\n", pid);
        if (getpid() == main_pid) {
            wait(&status);
            printf("My Second Son Died\n");
        }
        pause_system(5);
        printf("Done pauses\n");
    }
    else {
        for(int i = 0; i < 100; i++)
            printf("Child %d is running...\n", getpid());
        pause_system(5);
        printf("Child %d woke up, now dying\n", getpid());
    }
    print_stats();
}


void check() {
    int pid;
    pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 1000; i++)
            printf("ChildChildChild 1\n");
    }
    else {
        pid = fork();
        if (pid == 0) {
            for (int i = 0; i < 1000; i++)
                printf("Child 2\n");
        }
        else {
            for (int i = 0; i < 200; i++)
                printf("Parent\n");
            pause_system(10);
        }
    }
}



int main(int argc, char** argv){
    // env_freq();
    // env_large();
    example_pause_system(10,5,1000);
    // example_kill_system(10,1000);
    // mytest();
    // check();
    exit(0);
}
