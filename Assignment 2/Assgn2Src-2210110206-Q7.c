#include <stdio.h>
struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};
int main() {
    int num_processes, quantum, i, total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    struct Process processes[num_processes];
    printf("Enter burst time for each process:\n");
    for (i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
    int completed_processes = 0, time = 0;
    while (completed_processes < num_processes) {
        for (i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= quantum) {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time += time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed_processes++;
                } else {
                    time += quantum;
                    processes[i].waiting_time += time - quantum;
                    processes[i].remaining_time -= quantum;
                }
            }
            if (completed_processes == num_processes)
                break;
        }
    }
    for (i = 0; i < num_processes; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    float avg_waiting_time = (float)total_waiting_time / num_processes;
    float avg_turnaround_time = (float)total_turnaround_time / num_processes;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    return 0;
}