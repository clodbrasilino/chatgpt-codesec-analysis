#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long list_to_integer(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        errno = EINVAL;
        return 0;
    }

    errno = 0;
    long long result = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            errno = EINVAL;
            return 0;
        }

        if (result > (LLONG_MAX - list[i]) / 10) {
            errno = ERANGE;
            return 0;
        }

        result = result * 10 + list[i];
    }

    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    
    errno = 0;
    long long res1 = list_to_integer(list1, size1);
    if (errno != 0) {
        perror("list_to_integer failed");
        return EXIT_FAILURE;
    }
    printf("%lld\n", res1);

    int list2[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    
    errno = 0;
    long long res2 = list_to_integer(list2, size2);
    if (errno != 0) {
        perror("list_to_integer failed");
        return EXIT_FAILURE;
    }
    printf("%lld\n", res2);

    return EXIT_SUCCESS;
}