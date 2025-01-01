#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define MAX_THREADS 100
#define MAX_ACTIONS 300

typedef struct {
    int tid;
    int cs_num;
    char action[20];
    char timestamp[20];
} ActionInfo;

int n, k, t1, t2;
ActionInfo actions[MAX_ACTIONS];
int action_count = 0;
FILE *output_file;

void random_delay(int max_delay) {
    int delay = rand() % max_delay;
    usleep(delay);
}

void add_action(int tid, int cs_num, const char *action_name) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char timestr[20];
    strftime(timestr, sizeof(timestr), "%H:%M:%S", local);

    ActionInfo action;
    action.tid = tid;
    action.cs_num = cs_num;
    sprintf(action.action, "%s", action_name);
    sprintf(action.timestamp, "%s", timestr);

    actions[action_count++] = action;
}

void enter_cs(int tid, int cs_num) {
    add_action(tid, cs_num, "Entered");
    random_delay(t1);
    add_action(tid, cs_num, "Exited");
    usleep(t2);
}

void *thread_function(void *arg) {
    int tid = *((int *) arg);
    for (int i = 1; i <= k; i++) {
        add_action(tid, i, "Requested");
        enter_cs(tid, i);
    }
    return NULL;
}

int compare_actions(const void *a, const void *b) {
    const ActionInfo *action_a = (const ActionInfo *)a;
    const ActionInfo *action_b = (const ActionInfo *)b;
    if (action_a->cs_num != action_b->cs_num) {
        return action_a->cs_num - action_b->cs_num;
    }
    return action_a->tid - action_b->tid;
}

void write_sorted_actions() {
    qsort(actions, action_count, sizeof(ActionInfo), compare_actions);

    for (int i = 0; i < action_count; i++) {
        fprintf(output_file, "%dst CS %s at %s by thread %d\n", 
                actions[i].cs_num, actions[i].action, actions[i].timestamp, actions[i].tid);
    }
}

int main() {
    srand(time(NULL));

    FILE *finput = fopen("inp-params.txt", "r");
    if (finput == NULL) {
        perror("File error, check again.");
        return EXIT_FAILURE;
    }

    fscanf(finput, "%d %d %d %d", &n, &k, &t1, &t2);
    fclose(finput);

    output_file = fopen("output-tas.txt", "w");
    if (output_file == NULL) {
        perror("Output file creation error.");
        return EXIT_FAILURE;
    }

    clock_t start_time = clock();

    pthread_t threads[MAX_THREADS];
    int tids[MAX_THREADS];
    for (int i = 0; i < n; i++) {
        tids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &tids[i]) != 0) {
            perror("Thread creation error.");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread joining error.");
            return EXIT_FAILURE;
        }
    }

    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    write_sorted_actions();
    fprintf(output_file, "Total time taken: %.6f seconds\n", total_time);

    fclose(output_file);
    return 0;
}
