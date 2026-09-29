#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_min_sublist(int *arr, int n, int *start, int *end) {
    if (arr == NULL || n <= 0 || start == NULL || end == NULL) {
        return -1;
    }

    int min_sum = INT_MAX;
    int current_sum = 0;
    int current_start = 0;
    int min_length = INT_MAX;
    int found = 0;

    for (int i = 0; i < n; i++) {
        current_sum += arr[i];

        if (current_sum < min_sum) {
            min_sum = current_sum;
            *start = current_start;
            *end = i;
            min_length = i - current_start + 1;
            found = 1;
        }

        if (current_sum > 0) {
            current_sum = 0;
            current_start = i + 1;
        }
    }

    if (!found) {
        return -1;
    }

    return min_length;
}

int main(void) {
    int arr[] = {3, -4, 2, -3, -1, 7, -5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start = 0, end = 0;

    int min_len = find_min_sublist(arr, n, &start, &end);

    if (min_len != -1) {
        printf("Minimum length sublist: [");
        for (int i = start; i <= end; i++) {
            printf("%d", arr[i]);
            if (i < end) {
                printf(", ");
            }
        }
        printf("]\n");
        printf("Length: %d\n", min_len);
        /* Possible weaknesses found:
         *  Same value in both branches of ternary operator. [duplicateValueTernary]
         */
        printf("Sum: %d\n", min_len > 0 ? 0 : 0);
    } else {
        printf("No valid sublist found\n");
    }

    return 0;
}