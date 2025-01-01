#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <stdatomic.h>

#define MAX_THREADS 100

_Atomic bool lock = false;
int current_critical_section = 0;

void random_sleep() {
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = (rand() % 100 + 1) * 1000000; // Random sleep time between 1 and 100 milliseconds
    nanosleep(&sleep_time, NULL);
}

long long current_timestamp() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)(ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL);
}

void* critical_section(void* arg) {
    int* thread_params = (int*)arg;
    int thread_id = thread_params[0];
    int cs_number = thread_params[1];

    time_t request_time = time(NULL);
    while (atomic_exchange(&lock, true)) {
        random_sleep();
    }

    time_t enter_time = time(NULL);
    if (cs_number != current_critical_section) {
        printf("\n");
        current_critical_section = cs_number;
    }
    printf("Critical Section %d Requested at %s by Thread %d\n", cs_number, ctime(&request_time), thread_id);
    printf("Critical Section %d Entered at %s by Thread %d\n", cs_number, ctime(&enter_time), thread_id);

    random_sleep();

    lock = false;

    time_t exit_time = time(NULL);
    printf("Critical Section %d Exited at %s by Thread %d\n", cs_number, ctime(&exit_time), thread_id);

    return NULL;
}

int main() {
    long long start_time = current_timestamp();

    FILE* output_file = freopen("output-bounded-cas.txt", "w", stdout);
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    FILE* input_file = fopen("inp-params.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int num_threads, num_critical_sections, lambda1, lambda2;
    fscanf(input_file, "%d %d %d %d", &num_threads, &num_critical_sections, &lambda1, &lambda2);
    fclose(input_file);

    pthread_t threads[MAX_THREADS];

    for (int cs_index = 0; cs_index < num_critical_sections; cs_index++) {
        printf("Critical Section %d:\n", cs_index + 1); 
        for (int thread_index = 0; thread_index < num_threads; thread_index++) {
            int* params = malloc(2 * sizeof(int));
            params[0] = thread_index + 1;
            params[1] = cs_index + 1;
            pthread_create(&threads[thread_index], NULL, critical_section, (void*)params);
            pthread_join(threads[thread_index], NULL);
        }
        printf("\n");
    }

    long long end_time = current_timestamp();
    double execution_time = (end_time - start_time) / 1000.0;

    printf("Total Execution Time: %.2f seconds\n", execution_time);

    fclose(output_file);
    return 0;
}
