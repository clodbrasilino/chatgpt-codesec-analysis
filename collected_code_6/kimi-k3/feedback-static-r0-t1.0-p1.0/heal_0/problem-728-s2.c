#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_list(const int *list, size_t size, int *result) {
    if (list == NULL || result == NULL) {
        return -1;
    }
    if (size == 0) {
        *result = 0;
        return 0;
    }
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        if ((list[i] > 0 && sum > INT_MAX - list[i]) || 
            (list[i] < 0 && sum < INT_MIN - list[i])) {
            return -2;
        }
        sum += list[i];
    }
    *result = sum;
    return 0;
}

int sum_two_lists(const int *list1, size_t size1, const int *list2, size_t size2, int *result) {
    if (result == NULL) {
        return -1;
    }
    int sum1 = 0;
    int sum2 = 0;
    int status1 = sum_list(list1, size1, &sum1);
    int status2 = sum_list(list2, size2, &sum2);
    if (status1 != 0 || status2 != 0) {
        return -2;
    }
    if ((sum2 > 0 && sum1 > INT_MAX - sum2) || 
        (sum2 < 0 && sum1 < INT_MIN - sum2)) {
        return -2;
    }
    *result = sum1 + sum2;
    return 0;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {10, 20, 30, 40, 50};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result = 0;
    int status = sum_two_lists(list1, size1, list2, size2, &result);
    if (status == 0) {
        printf("Sum: %d\n", result);
    } else {
        fprintf(stderr, "Error: %d\n", status);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}