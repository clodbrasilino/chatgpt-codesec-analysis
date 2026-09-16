#include <stdio.h>
#include <stdlib.h>

size_t count_same_pair(const int *list1, const int *list2, const int *list3, size_t n)
{
    size_t count = 0;
    size_t i;

    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int list2[] = {2, 2, 3, 1, 2, 6, 7, 9, 9};
    int list3[] = {2, 1, 3, 1, 2, 6, 7, 9, 9};
    size_t n = sizeof(list1) / sizeof(list1[0]);
    size_t result;

    result = count_same_pair(list1, list2, list3, n);

    if (printf("Number of same pairs: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}