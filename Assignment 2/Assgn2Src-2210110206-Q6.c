#include <stdio.h>
#include <stdbool.h>
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    bool completed;
};
int main() {
    int num_processes, i, current_time = 0, smallest_index;
    float total_wait_time = 0, total_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    struct Process processes[num_processes];
    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
    }
    int completed_processes_count = 0;
    while (completed_processes_count < num_processes) {
        smallest_index = -1;
        for (i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (smallest_index == -1 || processes[i].remaining_time < processes[smallest_index].remaining_time) {
                    smallest_index = i;
                }
            }
        }
        if (smallest_index == -1) {
            current_time++;
            continue;
        }
        processes[smallest_index].remaining_time--;
        if (processes[smallest_index].remaining_time == 0) {
            completed_processes_count++;
            processes[smallest_index].completed = true;
            int turnaround_time = current_time + 1 - processes[smallest_index].arrival_time;
            int wait_time = turnaround_time - processes[smallest_index].burst_time;
            if (wait_time < 0) wait_time = 0;
            total_turnaround_time += turnaround_time;
            total_wait_time += wait_time;
        }

        current_time++;
    }
    float avg_wait_time = total_wait_time / num_processes;
    float avg_turnaround_time = total_turnaround_time / num_processes;
    printf("\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%.2f\t\t%.2f\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, (float)(current_time - processes[i].arrival_time),
               (float)((current_time - processes[i].arrival_time) - processes[i].burst_time));
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_wait_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    return 0;
}