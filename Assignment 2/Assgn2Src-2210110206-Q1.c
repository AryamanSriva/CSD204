#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int N; 
    printf("Enter the number of child processes (1 to 10): ");
    scanf("%d", &N);
    if (N < 1 || N > 10) {
        printf("Invalid number of child processes. Please enter a number between 1 and 10.\n");
        return 1;
    }
    pid_t pid;
    int i;
    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid == -1) {
            printf("Error in fork\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Hello, I am a child process. My PID is %d. My parent's PID is %d.\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
    }
    for (i = 0; i < N; i++) {
        wait(NULL);
        printf("I am a parent process. Reaped a child.\n");
    }
    return 0;
}