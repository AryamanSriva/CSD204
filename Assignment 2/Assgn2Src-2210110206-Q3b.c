#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void performBubbleSort(int array[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
int main() {
    int inputArray[100], numberOfElements, i;
    printf("Enter the number of elements: ");
    scanf("%d", &numberOfElements);
    printf("Enter the elements:\n");
    for (i = 0; i < numberOfElements; i++) {
        scanf("%d", &inputArray[i]);
    }
    pid_t childProcessID = fork();
    if (childProcessID == 0) {
        performBubbleSort(inputArray, numberOfElements);
        char numberOfElementsStr[10]; 
        char *arguments[numberOfElements + 3];
        arguments[0] = "./child_process";
        sprintf(numberOfElementsStr, "%d", numberOfElements);
        arguments[1] = numberOfElementsStr;
        for (int j = 0; j < numberOfElements; j++) {
            arguments[j + 2] = malloc(10 * sizeof(char));
            sprintf(arguments[j + 2], "%d", inputArray[j]);
        }
        arguments[numberOfElements + 2] = NULL;
        execv(arguments[0], arguments);
    } else {
        wait(NULL);
        printf("Parent process completed.\n");
    }
    return 0;
}
