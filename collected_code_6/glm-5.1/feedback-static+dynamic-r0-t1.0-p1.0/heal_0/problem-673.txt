#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long list_to_single_int(const int *list, size_t size) {
    long long result = 0;
    if (list == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            if (result < LLONG_MIN / 10 || (result == LLONG_MIN / 10 && list[i] < LLONG_MIN % 10)) {
                errno = ERANGE;
                return LLONG_MIN;
            }
            result = result * 10 + list[i];
        } else {
            if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && list[i] > LLONG_MAX % 10)) {
                errno = ERANGE;
                return LLONG_MAX;
            }
            result = result * 10 + list[i];
        }
    }
    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    long long res1 = list_to_single_int(list1, size1);
    if (errno == ERANGE) {
        perror("Conversion overflow");
        errno = 0;
    } else {
        printf("%lld\n", res1);
    }

    int list2[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    long long res2 = list_to_single_int(list2, size2);
    if (errno == ERANGE) {
        perror("Conversion overflow");
        errno = 0;
    } else {
        printf("%lld\n", res2);
    }

    long long res3 = list_to_single_int(NULL, 0);
    if (errno == ERANGE) {
        perror("Conversion overflow");
        errno = 0;
    } else {
        printf("%lld\n", res3);
    }

    return 0;
}