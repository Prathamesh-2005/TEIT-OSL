#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define STR 20
#define PAGE_NUM 10

void generate(int ref[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) ref[i] = rand() % PAGE_NUM;
}

void display(int ref[], int n) {
    printf("Page Reference String: ");
    for (int i = 0; i < n; i++) printf("%d ", ref[i]);
    printf("\n");
}

int fifo(int ref[], int n, int frames) {
    int frame[frames], front = 0, faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = ref[i], found = 0;
        for (int j = 0; j < frames; j++)
            if (page == frame[j]) { found = 1; break; }

        if (!found) {
            frame[front] = page;
            front = (front + 1) % frames;
            faults++;
        }
    }
    return faults;
}

int lru(int ref[], int n, int frames) {
    int frame[frames], counter[frames];
    int faults = 0, time = 0;

    for (int i = 0; i < frames; i++) { frame[i] = -1; counter[i] = 0; }

    for (int i = 0; i < n; i++) {
        int page = ref[i], found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                counter[j] = ++time;
                break;
            }
        }
        if (!found) {
            int min = 0;
            for (int j = 1; j < frames; j++)
                if (counter[j] < counter[min]) min = j;

            frame[min] = page;
            counter[min] = ++time;
            faults++;
        }
    }
    return faults;
}

int optimal(int ref[], int n, int frames) {
    int faults = 0;
    int frame[frames];

    // initialize frames
    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = ref[i];
        int found = 0;

        // check hit
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) { found = 1; break; }
        }

        if (!found) {
            int pos = -1;
            int farthest = -1; // index of farthest next use

            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == ref[k]) break;
                }

                // if frame[j] not used again, pick it
                if (k == n) { pos = j; break; }

                // else pick the page whose next use is farthest
                if (k > farthest) {
                    farthest = k;
                    pos = j;
                }
            }

            if (pos == -1) pos = 0; // fallback
            frame[pos] = page;
            faults++;
        }
    }

    return faults;
}

int main() {
    int ref[STR];
    int n = 13;                                  
    int given[] = {1,2,3,4,1,2,5,1,1,2,3,4,5};
    for (int i = 0; i < n; i++) ref[i] = given[i];

    display(ref, n);

    int f3_opt = optimal(ref, n, 3);
    int f4_opt = optimal(ref, n, 4);
    int f3_lru = lru(ref, n, 3);
    int f4_lru = lru(ref, n, 4);
    int f3_fifo = fifo(ref, n, 3);
    int f4_fifo = fifo(ref, n, 4);

    printf("\nFrame size 3 -> Optimal: %d, LRU: %d, FIFO: %d\n", f3_opt, f3_lru, f3_fifo);
    printf("Frame size 4 -> Optimal: %d, LRU: %d, FIFO: %d\n", f4_opt, f4_lru, f4_fifo);

    return 0;
}
