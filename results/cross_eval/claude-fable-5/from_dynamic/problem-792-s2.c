#include <stdio.h>
#include <stdlib.h>

size_t count_lists(int **lists, size_t total)
{
    size_t count = 0;
    size_t i;

    if (lists == NULL) {
        return 0;
    }

    for (i = 0; i < total; i++) {
        if (lists[i] != NULL) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int list1[] = {1, 3};
    int list2[] = {5, 7};
    int list3[] = {9, 11};
    int list4[] = {13, 15, 17};
    int *collection[4];
    size_t result;

    collection[0] = list1;
    collection[1] = list2;
    collection[2] = list3;
    collection[3] = list4;

    result = count_lists(collection, 4);
    if (printf("Number of lists: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = count_lists(NULL, 0);
    if (printf("Number of lists: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}