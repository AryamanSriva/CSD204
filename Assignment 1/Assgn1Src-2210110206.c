#include <stdio.h>

int main() {
    FILE *fp;
    char path[1035];

    // Open the command for reading.
    fp = popen("ps -eo pid,user,args", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }

    // Print the header
    printf("%-8s%-20s%s\n", "PID", "USER", "COMMAND");

    // Read the output a line at a time - output it.
    while (fgets(path, sizeof(path) - 1, fp) != NULL) {
        printf("%s", path);
    }

    // Close the file pointer.
    pclose(fp);

    return 0;
}