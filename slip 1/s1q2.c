#include <stdio.h>

int main()
{
    int page_reference_string[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
    int num_pages = sizeof(page_reference_string) / sizeof(page_reference_string[0]);
    int n, i, j, page, page_found, oldest_page_index = 0;
    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    int memory_frames[n];
    for (i = 0; i < n; i++) {
        memory_frames[i] = -1;
    }

    int page_faults = 0;

    for (i = 0; i < num_pages; i++) {
        page = page_reference_string[i];
        page_found = 0;

        for (j = 0; j < n; j++) {
            if (memory_frames[j] == page) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            memory_frames[oldest_page_index] = page;
            oldest_page_index = (oldest_page_index + 1) % n;
            page_faults++;
        }

        printf("Page reference: %d\nMemory Frames: ", page);
        for (j = 0; j < n; j++) {
            if (memory_frames[j] == -1)
                printf(" - ");
            else
                printf("%d ", memory_frames[j]);
        }
        printf("\n\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}

