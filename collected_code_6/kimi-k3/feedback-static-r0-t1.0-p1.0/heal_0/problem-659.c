#include <stdio.h>
#include <stdlib.h>

void print_duplicates(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    int *seen = (int *)malloc(size * sizeof(int));
    if (seen == NULL) {
        return;
    }

    size_t seen_count = 0;
    int *printed = (int *)malloc(size * sizeof(int));
    if (printed == NULL) {
        free(seen);
        return;
    }

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
    int arr[] = {1, 2, 3, 2, 4, 5, 1, 6, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    print_duplicates(arr, size);

    return 0;
}