#include <stdio.h>

int main() {
    int page_reference_string[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
    int n, i, j;
    
    printf("Enter the number of memory frames: ");
    scanf("%d", &n);
    
    int memory_frames[n];
    int page_queue[n];
    int page_faults = 0;

    // Initialize memory frames and page queue
    for (i = 0; i < n; i++) {
        memory_frames[i] = -1;
        page_queue[i] = -1;
    }

    // Process each page reference
    for (i = 0; i < sizeof(page_reference_string) / sizeof(page_reference_string[0]); i++) {
        int page = page_reference_string[i];
        int found = 0;

        // Check if the page is already in memory frames
        for (j = 0; j < n; j++) {
            if (memory_frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, we have a page fault
        if (!found) {
            page_faults++;

            // If the page queue is not empty, replace the oldest page
            if (page_queue[0] != -1) {
                int replaced_page = page_queue[0];

                // Replace the page in memory frames
                for (j = 0; j < n; j++) {
                    if (memory_frames[j] == replaced_page) {
                        memory_frames[j] = page;
                        break;
                    }
                }

                // Shift the page queue to remove the oldest page
                for (j = 0; j < n - 1; j++) {
                    page_queue[j] = page_queue[j + 1];
                }
            } else {
                // If there is an empty frame, just add the page
                for (j = 0; j < n; j++) {
                    if (memory_frames[j] == -1) {
                        memory_frames[j] = page;
                        break;
                    }
                }
            }

            // Update the page queue
            for (j = 0; j < n - 1; j++) {
                page_queue[j] = page_queue[j + 1];
            }
            page_queue[n - 1] = page;  // Add the new page to the end of the queue
        }

        // Display the current state of memory frames and page queue
        printf("Page reference: %d\n", page);
        printf("Memory Frames: ");
        for (j = 0; j < n; j++) {
            printf("%d ", memory_frames[j]);
        }
        printf("\nPage Queue: ");
        for (j = 0; j < n; j++) {
            printf("%d ", page_queue[j]);
        }
        printf("\n\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}
