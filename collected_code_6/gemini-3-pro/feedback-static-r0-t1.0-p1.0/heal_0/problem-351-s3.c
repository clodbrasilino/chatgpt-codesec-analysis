#include <stdio.h>
#include <stdlib.h>

struct ElementCount {
    int value;
    int count;
};

int firstElementKTimes(const int* arr, size_t n, int k) {
    if (arr == NULL || n == 0 || k <= 0) {
        return -1;
    }

    struct ElementCount* counts = (struct ElementCount*)malloc(n * sizeof(struct ElementCount));
    if (counts == NULL) {
        return -1;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < n; ++i) {
        int found = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (counts[j].value == arr[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[unique_count].value = arr[i];
            counts[unique_count].count = 1;
            unique_count++;
        }
    }

    int result = -1;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < unique_count; ++j) {
            if (counts[j].value == arr[i] && counts[j].count == k) {
                result = arr[i];
                free(counts);
                return result;
            }
        }
    }

    free(counts);
    return result;
}

int main(void) {
    int arr[] = { 1, 7, 4, 3, 4, 8, 7 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    int result = firstElementKTimes(arr, n, k);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Not found\n");
    }

    return 0;
}