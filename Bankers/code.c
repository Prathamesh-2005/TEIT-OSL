#include <stdio.h>

void calculateNeed(int n, int m, int max[n][m], int alloc[n][m], int need[n][m]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

void bankersAlgorithm(int n, int m, int alloc[n][m], int max[n][m], int avail[m]) {
    int need[n][m];
    calculateNeed(n, m, max, alloc, need);

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    int finish[n], safeSeq[n], index = 0;
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canRun = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[index++] = i;
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if (found == 0) {
            printf("\nSystem is in an UNSAFE state!\n");
            return;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
    for (int i = 0; i < n - 1; i++)
        printf("P%d -> ", safeSeq[i]);
    printf("P%d\n", safeSeq[n - 1]);
}

// Main function
int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources (%d):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Call the banker’s algorithm function
    bankersAlgorithm(n, m, alloc, max, avail);

    return 0;
}
