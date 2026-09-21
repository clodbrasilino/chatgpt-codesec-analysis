#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

bool contains_consecutive_numbers(const int *list, size_t size)
{
    int *copy = NULL;
    size_t i;
    size_t bytes;
    bool result = true;

    if (list == NULL || size == 0U) {
        return false;
    }

    if (size == 1U) {
        return true;
    }

    if (size > SIZE_MAX / sizeof(int)) {
        return false;
    }

    bytes = size * sizeof(int);

    copy = malloc(bytes);
    if (copy == NULL) {
        return false;
    }

    for (i = 0U; i < size; i++) {
        copy[i] = list[i];
    }

    qsort(copy, size, sizeof(int), compare_ints);

    for (i = 1U; i < size; i++) {
        if (copy[i - 1U] == INT_MAX || copy[i] != copy[i - 1U] + 1) {
            result = false;
            break;
        }
    }

    free(copy);
    return result;
}

int main(void)
{
    int list1[] = {3, 4, 5, 6, 7};
    int list2[] = {10, 12, 11, 14};
    int list3[] = {2, 3, 1, 4, 5};

    if (contains_consecutive_numbers(list1, sizeof(list1) / sizeof(list1[0]))) {
        printf("list1 contains consecutive numbers\n");
    } else {
        printf("list1 does not contain consecutive numbers\n");
    }

    if (contains_consecutive_numbers(list2, sizeof(list2) / sizeof(list2[0]))) {
        printf("list2 contains consecutive numbers\n");
    } else {
        printf("list2 does not contain consecutive numbers\n");
    }

    if (contains_consecutive_numbers(list3, sizeof(list3) / sizeof(list3[0]))) {
        printf("list3 contains consecutive numbers\n");
    } else {
        printf("list3 does not contain consecutive numbers\n");
    }

    return EXIT_SUCCESS;
}