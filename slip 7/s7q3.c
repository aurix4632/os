#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0, i;
    for (i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int lru_page_replacement(int pages[], int n, int frames) {
    int memory_frames[frames], time[frames], counter = 0, page_faults = 0;
    int i, j, pos;

    for (i = 0; i < frames; i++) {
        memory_frames[i] = -1;
        time[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (memory_frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            page_faults++;
            if (i < frames) {
                memory_frames[i] = pages[i];
                counter++;
                time[i] = counter;
            } else {
                pos = findLRU(time, frames);
                memory_frames[pos] = pages[i];
                counter++;
                time[pos] = counter;
            }
        }

        printf("Page %d -> Memory: ", pages[i]);
        for (j = 0; j < frames; j++) {
            if (memory_frames[j] == -1)
                printf("- ");
            else
                printf("%d ", memory_frames[j]);
        }
        printf("\n");
    }

    return page_faults;
}

int main() {
    int frames, page_faults;
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    printf("Enter the number of memory frames: ");
    scanf("%d", &frames);

    page_faults = lru_page_replacement(pages, n, frames);

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
