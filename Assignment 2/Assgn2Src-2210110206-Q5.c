#include <stdio.h>
struct Job {
    int id;
    int duration;
    int wait_time;
    int turnaround_time;
};
void swap(struct Job *a, struct Job *b) {
    struct Job temp = *a;
    *a = *b;
    *b = temp;
}
void sort_by_duration(struct Job jobs[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (jobs[j].duration < jobs[min_idx].duration) {
                min_idx = j;
            }
        }
        swap(&jobs[min_idx], &jobs[i]);
    }
}
int main() {
    int num_jobs, i;
    printf("Enter the number of jobs: ");
    scanf("%d", &num_jobs);
    struct Job jobs[num_jobs];
    float total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter duration for each job:\n");
    for (i = 0; i < num_jobs; i++) {
        jobs[i].id = i + 1;
        printf("Duration for job %d: ", i + 1);
        scanf("%d", &jobs[i].duration);
    }
    sort_by_duration(jobs, num_jobs);
    jobs[0].wait_time = 0;
    jobs[0].turnaround_time = jobs[0].duration;
    total_turnaround_time += jobs[0].turnaround_time;
    for (i = 1; i < num_jobs; i++) {
        jobs[i].wait_time = jobs[i - 1].wait_time + jobs[i - 1].duration;
        jobs[i].turnaround_time = jobs[i].wait_time + jobs[i].duration;
        total_waiting_time += jobs[i].wait_time;
        total_turnaround_time += jobs[i].turnaround_time;
    }
    float avg_waiting_time = total_waiting_time / num_jobs;
    float avg_turnaround_time = total_turnaround_time / num_jobs;
    printf("\nJob\tDuration\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_jobs; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", jobs[i].id, jobs[i].duration, jobs[i].wait_time, jobs[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    return 0;
}