#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_second_smallest(const int *list, size_t size) {
    if (list == NULL || size < 2) {
        return INT_MIN;
    }

    int smallest = list[0];
    int second_smallest = INT_MAX;

    for (size_t i = 1; i < size; ++i) {
        if (list[i] < smallest) {
            second_smallest = smallest;
            smallest = list[i];
        } else if (list[i] < second_smallest && list[i] != smallest) {
            second_smallest = list[i];
        }
    }

    if (second_smallest == INT_MAX) {
        return INT_MIN;
    }

    return second_smallest;
}

int main(void) {
    int list1[] = {5, 2, 8, 1, 9, 3};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = find_second_smallest(list1, size1);
    printf("Second smallest: %d\n", result1);

    int list2[] = {7, 7, 7, 7};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = find_second_smallest(list2, size2);
    printf("Second smallest: %d\n", result2);

    int list3[] = {42};
    size_t size3 = 1;
    int result3 = find_second_smallest(list3, size3);
    printf("Second smallest: %d\n", result3);

    return 0;
}