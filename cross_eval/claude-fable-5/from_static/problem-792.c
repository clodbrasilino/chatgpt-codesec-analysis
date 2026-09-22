#include <stdio.h>
#include <stdlib.h>

size_t count_lists(int **lists, size_t max_lists)
{
    size_t count = 0;

    if (lists == NULL) {
        return 0;
    }

    for (size_t i = 0; i < max_lists; i++) {
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

    int *lists[] = {list1, list2, list3, list4};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    size_t result = count_lists(lists, num_lists);

    if (printf("Number of lists: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = count_lists(NULL, 0);

    if (printf("Number of lists (NULL input): %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}