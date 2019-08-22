#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void printFormatFirst (int pid, int ppid, int seconds){
    printf("1. pid %d, ppid %d, lifetime %d\n", pid, ppid, seconds);
}
void printFormatSecond (int pid, int ppid, int seconds){
    printf("\t2. pid %d, ppid %d, lifetime %d\n", pid, ppid, seconds);
}
void printFormatThird (int pid, int ppid, int seconds){
    printf("\t\t3. pid %d, ppid %d, lifetime %d\n", pid, ppid, seconds);
}
void printFormatFourth (int pid, int ppid, int seconds){
    printf("\t\t\t4. pid %d, ppid %d, lifetime %d\n", pid, ppid, seconds);
}

int main()
{
    for (int i = 1; i <= 5; i++){
        sleep(1);
        printFormatFirst(getpid(), getppid(), i);
    }
    pid_t second;
    second = fork();
    switch (second){
        case -1:
            printf("Error creating child process...\n");
            break;
        case 0:
            // second
            for (int i = 1; i <= 6; i++){
                sleep(1);
                printFormatSecond(getpid(), getppid(), i);
            }
            pid_t fourth;
            fourth=fork();
            switch (fourth){
                case -1:
                    printf("Error creating child process...\n");
                    break;
                case 0:
                    // fourth
                    for (int i = 1; i <= 9; i++){
                        sleep(1);
                        printFormatFourth(getpid(), getppid(), i);
                    }
                    break;
                
                default:
                    // second
                    for (int i = 7; i <= 13; i++){
                        sleep(1);
                        printFormatSecond(getpid(), getppid(), i);
                    }
                    break;
            }
            break;
        
        default:
            // first
            for (int i = 6; i <= 9; i++){
                sleep(1);
                printFormatFirst(getpid(), getppid(), i);
            }
            pid_t third;
            third=fork();
            switch (third){
                case -1:
                    printf("Error creating child process...\n");
                    break;
                case 0:
                    // third
                    for (int i = 1; i <= 7; i++){
                        sleep(1);
                        printFormatThird(getpid(), getppid(), i);
                    }
                    break;
                
                default:
                    // first
                    for (int i = 10; i <= 13; i++){
                        sleep(1);
                        printFormatFirst(getpid(), getppid(), i);
                    }
                    break;
            }
            break;
    }
    exit(0);
}
