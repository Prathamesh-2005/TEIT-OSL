#include <stdio.h>

struct Process {
    char name[10];
    int at, bt;    
    int ct, tat, wt; // Completion, Turnaround, Waiting
};

// Function to print Gantt Chart
void printGanttChart(struct Process p[], int order[], int order_ct[], int count, int start_time) {
    printf("\nGANTT CHART:\n");
    printf("_________________________________\n|");
    for (int i = 0; i < count; i++) {
        printf(" %s |", p[order[i]].name);
    }
    printf("\n_________________________________\n");

    printf("%d", start_time);
    for (int i = 0; i < count; i++)
        printf("    %d", order_ct[i]);
    printf("\n");
}

// FCFS Scheduling
void findAvgTime_FCFS(struct Process p[], int n) {
    int time = 0, total_wt = 0, total_tat = 0;

    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    int order[10], order_ct[10], k = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;  // CPU idle until process arrives

        p[i].ct = time + p[i].bt;      // Completion Time
        p[i].tat = p[i].ct - p[i].at;  // Turnaround Time
        p[i].wt = p[i].tat - p[i].bt;  // Waiting Time

        time = p[i].ct;

        order[k] = i;
        order_ct[k] = p[i].ct;
        k++;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printGanttChart(p, order, order_ct, k, p[0].at);

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

// SJF (Non-Preemptive)
void findAvgTime_SJF(struct Process p[], int n) {
    int completed = 0, time = 0, total_wt = 0, total_tat = 0;
    int isCompleted[10] = {0};
    int order[10], order_ct[10], k = 0;

    // Find earliest arrival time
    int earliest_at = p[0].at;
    for (int i = 1; i < n; i++)
        if (p[i].at < earliest_at)
            earliest_at = p[i].at;

    time = earliest_at;

    while (completed != n) {
        int idx = -1, min_bt = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !isCompleted[i]) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            isCompleted[idx] = 1;
            completed++;

            order[k] = idx;
            order_ct[k] = p[idx].ct;
            k++;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        } else {
            time++;  // CPU idle
        }
    }

    printGanttChart(p, order, order_ct, k, earliest_at);

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n, choice;
    struct Process p[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Process details:\n");
    printf("Process  Arrival_Time  Burst_Time\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].name, &p[i].at, &p[i].bt);
    }

    do {
        printf("\nEnter the choice:\n1. FCFS\n2. SJF (non-preemptive)\n3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                findAvgTime_FCFS(p, n);
                break;
            case 2:
                findAvgTime_SJF(p, n);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
