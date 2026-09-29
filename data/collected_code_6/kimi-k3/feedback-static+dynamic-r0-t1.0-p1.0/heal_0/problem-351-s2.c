#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int count;
    int first_index;
} ElementInfo;

int find_first_k_times(const int *arr, size_t n, int k, int *result) {
    if (arr == NULL || n == 0 || k <= 0 || result == NULL) {
        return 0;
    }

    ElementInfo *info = malloc(n * sizeof(*info));
    if (info == NULL) {
        return 0;
    }

    size_t info_count = 0;
    int found = 0;
    int min_index = INT_MAX;

    for (size_t i = 0; i < n; i++) {
        size_t j = 0;
        while (j < info_count && info[j].value != arr[i]) {
            j++;
        }

        if (j == info_count) {
            info[j].value = arr[i];
            info[j].count = 1;
            info[j].first_index = (int)i;
            info_count++;
        } else {
            info[j].count++;
            if (info[j].count == k && info[j].first_index < min_index) {
                min_index = info[j].first_index;
                *result = arr[i];
                found = 1;
            }
        }
    }

    free(info);
    return found;
}

int main(void) {
    int arr[] = {1, 7, 4, 3, 4, 8, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result;

    if (find_first_k_times(arr, n, k, &result)) {
        printf("First element occurring %d times: %d\n", k, result);
    } else {
        printf("No element occurs %d times\n", k);
    }

    return 0;
}