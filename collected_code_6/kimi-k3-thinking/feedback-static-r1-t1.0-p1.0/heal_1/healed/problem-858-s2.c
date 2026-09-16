#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

int count_lists_squared(const int *const lists[], size_t *count_out, size_t *squared_out)
{
    size_t count = 0;

    if (squared_out == NULL) {
        return -1;
    }

    if (lists != NULL) {
        while (lists[count] != NULL) {
            count++;
        }
    }

    if (count > 0 && count > SIZE_MAX / count) {
        return -1;
    }

    if (count_out != NULL) {
        *count_out = count;
    }

    *squared_out = count * count;
    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {6, 7, 8, 9};
    int list4[] = {10, 11};
    const int *list_of_lists[] = {list1, list2, list3, list4, NULL};
    size_t count = 0;
    size_t squared = 0;

    if (count_lists_squared(list_of_lists, &count, &squared) != 0) {
        fprintf(stderr, "Error: failed to compute squared list count\n");
        return 1;
    }

    printf("Number of lists: %zu\n", count);
    printf("Squared count: %zu\n", squared);

    return 0;
}