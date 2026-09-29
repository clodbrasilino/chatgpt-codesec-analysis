#include <stdio.h>
#include <stdlib.h>

int count_lists_squared(int **list_of_lists, size_t num_lists);

int count_lists_squared(int **list_of_lists, size_t num_lists)
{
    size_t count = 0;
    size_t i;

    if (list_of_lists == NULL) {
        return 0;
    }

    for (i = 0; i < num_lists; i++) {
        if (list_of_lists[i] != NULL) {
            count++;
        }
    }

    if (count > 46340U) {
        return -1;
    }

    return (int)(count * count);
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {6, 7, 8, 9};
    int *list_of_lists[3];
    int result;

    list_of_lists[0] = list1;
    list_of_lists[1] = list2;
    list_of_lists[2] = list3;

    result = count_lists_squared(list_of_lists, 3);

    if (result < 0) {
        fprintf(stderr, "Error: count too large to square safely\n");
        return EXIT_FAILURE;
    }

    if (printf("Squared count of lists: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = count_lists_squared(NULL, 0);

    if (printf("Squared count of empty input: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}