#include <stdio.h>
int main() {
    int num_processes, i;
    printf("Enter the number of processes in the ready queue: ");
    scanf("%d", &num_processes);
    int burst_time[num_processes], waiting_time[num_processes], turnaround_time[num_processes];
    float total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter the burst time for each process:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    waiting_time[0] = 0;
    for (i = 1; i < num_processes; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }
    for (i = 0; i < num_processes; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }
    for (i = 0; i < num_processes; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    float avg_waiting_time = total_waiting_time / num_processes;
    float avg_turnaround_time = total_turnaround_time / num_processes;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    return 0;
}