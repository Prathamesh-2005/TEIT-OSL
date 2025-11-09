//ps -elf | grep defunct
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n], arr_copy[n];
    printf("Enter %d integers: ", n);
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i];
    }

    printf("\n--- ZOMBIE DEMO ---\n");
    pid_t pid1 = fork();
    
    if(pid1 == 0) {
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        insertionSort(arr_copy, n);
        printf("Child sorted: ");
        for(int i=0; i<n; i++) printf("%d ", arr_copy[i]);
        printf("\nChild exiting...\n");
        exit(0);
    } else {
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid1);
        bubbleSort(arr, n);
        printf("Parent sorted: ");
        for(int i=0; i<n; i++) printf("%d ", arr[i]);
        printf("\nParent sleeping (Child %d is ZOMBIE now)...\n", pid1);
        printf("Check zombie: ps -ef | grep defunct\n");
        sleep(5);
        wait(NULL);
        printf("Zombie cleaned!\n\n");
    }

    printf("--- ORPHAN DEMO ---\n");
    pid_t pid2 = fork();
    
    if(pid2 == 0) {
        printf("Child PID: %d, Parent PID before: %d\n", getpid(), getppid());
        sleep(3);
        printf("Child PID: %d, Parent PID after: %d (orphaned!)\n", getpid(), getppid());
        exit(0);
    } else {
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid2);
        printf("Parent exiting...\n");
        exit(0);
    }
}