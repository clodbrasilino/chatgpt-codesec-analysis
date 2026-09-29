#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

bool contains_consecutive(const int *arr, size_t size)
{
    if (arr == NULL || size < 2)
        return false;

    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL)
        return false;

    for (size_t i = 0; i < size; i++)
        sorted[i] = arr[i];

    qsort(sorted, size, sizeof(int), compare_ints);

    bool found = false;
    for (size_t i = 0; i < size - 1; i++)
    {
        if (sorted[i] != INT_MAX && sorted[i + 1] == sorted[i] + 1)
        {
            found = true;
            break;
        }
    }

    free(sorted);
    return found;
}

int main(void)
{
    int list1[] = {1, 2, 3, 5, 7};
    int list2[] = {10, 15, 20, 25};
    int list3[] = {5, 4, 2, 3, 1};
    int list4[] = {100};
    int list5[] = {INT_MAX, INT_MAX - 1};

    printf("List1: %s\n", contains_consecutive(list1, 5) ? "true" : "false");
    printf("List2: %s\n", contains_consecutive(list2, 4) ? "true" : "false");
    printf("List3: %s\n", contains_consecutive(list3, 5) ? "true" : "false");
    printf("List4: %s\n", contains_consecutive(list4, 1) ? "true" : "false");
    printf("List5: %s\n", contains_consecutive(list5, 2) ? "true" : "false");

    return 0;
}