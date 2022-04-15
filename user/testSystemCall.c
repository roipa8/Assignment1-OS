#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char** argv){
    int a=pause_system(5);
    printf("%d\n",a);
    exit(0);
}