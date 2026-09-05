#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_max_difference(const int *arr, size_t size, int *result)
{
    size_t i;
    int min_val;
    int max_diff;

    if (arr == NULL || result == NULL || size < 2) {
        return -1;
    }

    min_val = arr[0];
    max_diff = 0;

    for (i = 1; i < size; i++) {
        int diff;
        
        if (arr[i] > min_val) {
            if ((arr[i] > 0 && min_val < 0 && arr[i] > INT_MAX + min_val) ||
                (arr[i] < 0 && min_val > 0 && arr[i] < INT_MIN + min_val)) {
                return -2;
            }
            diff = arr[i] - min_val;
            if (diff > max_diff) {
                max_diff = diff;
            }
        } else {
            min_val = arr[i];
        }
    }

    *result = max_diff;
    return 0;
}

int main(void)
{
    int arr[] = {2, 3, 10, 6, 4, 8, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;
    int status;

    status = find_max_difference(arr, size, &result);
    
    if (status == 0) {
        printf("Maximum difference: %d\n", result);
    } else if (status == -2) {
        fprintf(stderr, "Error: Integer overflow detected\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}