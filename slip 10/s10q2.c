#include <stdio.h>

#define MAX 100

// Function to find the index of the page to be replaced using the Optimal algorithm
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
            return i;
        }
    }

    return (page_index == -1) ? 0 : page_index;
}

// Function to implement the Optimal Page Replacement algorithm
void optimal_page_replacement(int ref_string[], int ref_size, int num_frames) {
    int frames[num_frames];
    int i, j, page_faults = 0;

    // Initialize frames with -1 to indicate empty slots
    for (i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("\nPage scheduling:\n");
    for (i = 0; i < ref_size; i++) {
        int page = ref_string[i];
        int found = 0;

        // Check if the page is already in the frames
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            page_faults++;

            if (i < num_frames) {
                // If there is space in frames, insert the page into the next empty frame
                frames[i] = page;
            } else {
                // Replace a page using the Optimal algorithm
                int replace_index = find_optimal(frames, ref_string, ref_size, i, num_frames);
                frames[replace_index] = page;
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

    printf("\nTotal number of page faults: %d\n", page_faults);
}

int main() {
    int ref_string[MAX], ref_size, num_frames;

    // Input reference string size and elements
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &ref_size);

    printf("Enter the reference string: ");
    for (int i = 0; i < ref_size; i++) {
        scanf("%d", &ref_string[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    // Call the optimal page replacement function
    optimal_page_replacement(ref_string, ref_size, num_frames);

    return 0;
}
