#include <stdio.h>

#define MAX 100

int find_optimal(int frames[], int ref_string[], int ref_size, int current_pos, int num_frames) {
    int i, j, farthest = current_pos, page_index = -1;

    for (i = 0; i < num_frames; i++) {
        int found = 0;
        for (j = current_pos + 1; j < ref_size; j++) {
            if (frames[i] == ref_string[j]) {
                if (j > farthest) {
                    farthest = j;
                    page_index = i;
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            return i; // Return index of empty frame
        }
    }

    return (page_index == -1) ? 0 : page_index; // Return the index of the page to replace
}

void optimal_page_replacement(int ref_string[], int ref_size, int num_frames) {
    int frames[num_frames];
    int i, j, page_faults = 0;

    for (i = 0; i < num_frames; i++) {
        frames[i] = -1; // Initialize frames with -1 to indicate empty slots
    }

    printf("Page scheduling:\n");
    for (i = 0; i < ref_size; i++) {
        int page = ref_string[i];
        int found = 0;

        for (j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1; // Page is already in frames
                break;
            }
        }

        if (!found) {
            page_faults++;

            if (i < num_frames) {
                frames[i] = page; // Insert the page into the next empty frame
            } else {
                int replace_index = find_optimal(frames, ref_string, ref_size, i, num_frames);
                frames[replace_index] = page; // Replace a page using the Optimal algorithm
            }

            // Print the current state of frames
            printf("Page %d: ", page);
            for (j = 0; j < num_frames; j++) {
                if (frames[j] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[j]);
            }
            printf("\n");
        }
    }

    printf("Total number of page faults: %d\n", page_faults);
}

int main() {
    int ref_string[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int num_frames = 3;
    int ref_size = sizeof(ref_string) / sizeof(ref_string[0]);

    optimal_page_replacement(ref_string, ref_size, num_frames);

    return 0;
}
