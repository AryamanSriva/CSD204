#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdatomic.h>

int n, k;
double lambda1, lambda2;
_Atomic int shared_variable = 0;

double exponential_delay(double lambda) {
    double u = rand() / (RAND_MAX + 1.0);
    return -log(1 - u) / lambda;
}

char* current_datetime() {
    time_t now = time(NULL);
    return ctime(&now);
}

void *critical_section(void *arg) {
    int thread_id = *((int *)arg);
    srand(time(NULL) + thread_id); 

    for (int i = 0; i < k; i++) {
        while (atomic_load(&shared_variable) != thread_id - 1) {
            usleep(100); 
        }

        FILE *output_file = fopen("output-cas.txt", "a"); 
        if (output_file == NULL) {
            fprintf(stderr, "Error opening output file.\n");
            return NULL;
        }
        fprintf(output_file, "%dst CS Requested by Thread %d at %s", i + 1, thread_id, current_datetime());
        fprintf(output_file, "%dst CS Entered by Thread %d at %s", i + 1, thread_id, current_datetime());
        fclose(output_file);

        usleep((useconds_t) (rand() % 1000000));

        output_file = fopen("output-cas.txt", "a"); 
        if (output_file == NULL) {
            fprintf(stderr, "Error opening output file.\n");
            return NULL;
        }
        fprintf(output_file, "%dst CS Exited by Thread %d at %s", i + 1, thread_id, current_datetime());
        fclose(output_file);

        atomic_store(&shared_variable, (thread_id % n));
    }

    return NULL;
}

int main() {
    clock_t start_time = clock(); 

    FILE *input_file = fopen("inp-params.txt", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    fscanf(input_file, "%d %d %lf %lf", &n, &k, &lambda1, &lambda2);
    fclose(input_file);

    pthread_t threads[n];
    int thread_ids[n];

    for (int i = 0; i < n; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, critical_section, &thread_ids[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock(); 
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; 

    FILE *output_file = fopen("output-cas.txt", "a");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }
    fprintf(output_file, "Total execution time: %.3f seconds\n", total_time);
    fclose(output_file);

    return 0;
}
