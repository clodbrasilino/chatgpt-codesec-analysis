#include <stdio.h>
#include <stdlib.h>

void flip(int arr[], int end) {
    int start = 0;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void pancake_sort(int arr[], int n) {
    for (int curr_size = n; curr_size > 1; --curr_size) {
        int max_idx = 0;
        for (int i = 1; i < curr_size; ++i) {
            if (arr[i] > arr[max_idx]) {
                max_idx = i;
            }
        }

        if (max_idx == curr_size - 1) {
            continue;
        }

        if (max_idx > 0) {
            flip(arr, max_idx);
        }

        flip(arr, curr_size - 1);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0') {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    pancake_sort(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}