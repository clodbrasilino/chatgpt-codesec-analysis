#include <stdio.h>
#include <stdlib.h>

int count_same_pair(const int *list1, const int *list2, const int *list3, size_t n)
{
    size_t i;
    int count = 0;

    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        return -1;
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
    const int list1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const int list2[] = {2, 2, 3, 1, 2, 6, 7, 9};
    const int list3[] = {2, 1, 3, 1, 2, 6, 7, 9};
    size_t n = sizeof(list1) / sizeof(list1[0]);
    int result;

    result = count_same_pair(list1, list2, list3, n);
    if (result < 0) {
        fprintf(stderr, "Error: invalid input lists\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of same pairs: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}