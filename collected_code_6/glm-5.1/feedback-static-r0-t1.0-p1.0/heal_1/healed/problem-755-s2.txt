#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_second_smallest(const int *list, size_t size) {
    if (list == NULL || size < 2) {
        exit(EXIT_FAILURE);
    }

    int smallest = list[0];
    int second_smallest = INT_MAX;
    int found = 0;

    for (size_t i = 1; i < size; i++) {
        if (list[i] < smallest) {
            second_smallest = smallest;
            smallest = list[i];
            found = 1;
        } else if (list[i] > smallest) {
            if (!found || list[i] < second_smallest) {
                second_smallest = list[i];
                found = 1;
            }
        }
    }

    if (!found) {
        exit(EXIT_FAILURE);
    }

    return second_smallest;
}

int main(void) {
    int arr1[] = {12, 13, 1, 10, 34, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = find_second_smallest(arr1, size1);
    printf("%d\n", res1);

    int arr2[] = {-5, -2, -8, -1, -8};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = find_second_smallest(arr2, size2);
    printf("%d\n", res2);

    return 0;
}