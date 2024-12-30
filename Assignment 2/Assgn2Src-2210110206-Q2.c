#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void bubbleSort(int numbers[], int size) {
    int i, j, temp;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (numbers[j] > numbers[j+1]) {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }
}
void displayArray(int numbers[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}
int main() {
    int size, i;
    printf("Please provide the count of numbers: ");
    scanf("%d", &size);
    int numbers[size], copy[size];
    printf("Enter %d numbers: ", size);
    for (i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
        copy[i] = numbers[i]; 
    }
    pid_t pid = fork();
    if (pid == -1) {
        printf("Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child process is sorting using bubble sort:\n");
        bubbleSort(copy, size);
        printf("Sorted array by child process: ");
        displayArray(copy, size);
        exit(EXIT_SUCCESS);
    } else {
        printf("Parent process is sorting using selection sort:\n");
        int minIndex, temp;
        for (i = 0; i < size-1; i++) {
            minIndex = i;
            for (int j = i+1; j < size; j++) {
                if (numbers[j] < numbers[minIndex]) {
                    minIndex = j;
                }
            }
            temp = numbers[i];
            numbers[i] = numbers[minIndex];
            numbers[minIndex] = temp;
        }
        printf("Sorted array by parent process: ");
        displayArray(numbers, size);
        wait(NULL);
    }
    return 0;
}