#include <stdio.h>
#include <stdlib.h>

void print_duplicates(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    int *seen = (int *)calloc(size, sizeof(int));
    int *printed = (int *)calloc(size, sizeof(int));
    
    if (seen == NULL || printed == NULL) {
        free(seen);
        free(printed);
        return;
    }

    size_t seen_count = 0;
    size_t printed_count = 0;

    for (size_t i = 0; i < size; i++) {
        int is_seen = 0;
        for (size_t j = 0; j < seen_count; j++) {
            if (seen[j] == arr[i]) {
                is_seen = 1;
                break;
            }
        }

        if (is_seen) {
            int is_printed = 0;
            for (size_t j = 0; j < printed_count; j++) {
                if (printed[j] == arr[i]) {
                    is_printed = 1;
                    break;
                }
            }

            if (!is_printed) {
                printf("%d\n", arr[i]);
                printed[printed_count++] = arr[i];
            }
        } else {
            seen[seen_count++] = arr[i];
        }
    }

    free(seen);
    free(printed);
}

int main(void) {
    int arr[] = {4, 3, 2, 7, 8, 2, 3, 1, 4, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    printf("Duplicates:\n");
    print_duplicates(arr, size);

    return 0;
}