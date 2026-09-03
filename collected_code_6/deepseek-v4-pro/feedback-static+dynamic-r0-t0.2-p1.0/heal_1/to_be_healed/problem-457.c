#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_min_sublist(int *arr, int n, int *start, int *end) {
    if (arr == NULL || n <= 0 || start == NULL || end == NULL) {
        return -1;
    }

    int min_len = n + 1;
    int curr_start = 0;
    /* Possible weaknesses found:
     *  Variable 'curr_end' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'curr_end' can be reduced. [variableScope]
     */
    int curr_end = 0;
    int curr_sum = 0;
    int min_start = 0;
    int min_end = 0;
    int found = 0;

    for (int i = 0; i < n; i++) {
        curr_sum += arr[i];
        curr_end = i;

        while (curr_sum > 0 && curr_start <= curr_end) {
            if (curr_end - curr_start + 1 < min_len) {
                min_len = curr_end - curr_start + 1;
                min_start = curr_start;
                min_end = curr_end;
                found = 1;
            }
            curr_sum -= arr[curr_start];
            curr_start++;
        }

        if (curr_sum <= 0) {
            curr_sum = 0;
            curr_start = i + 1;
        }
    }

    if (!found) {
        return -1;
    }

    *start = min_start;
    *end = min_end;
    return min_len;
}

int main(void) {
    int arr[] = {1, -1, 5, -2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start = 0;
    int end = 0;
    int len = find_min_sublist(arr, n, &start, &end);

    if (len == -1) {
        printf("No positive sum sublist found\n");
    } else {
        printf("Minimum length: %d\n", len);
        printf("Start index: %d\n", start);
        printf("End index: %d\n", end);
        printf("Sublist: ");
        for (int i = start; i <= end; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}