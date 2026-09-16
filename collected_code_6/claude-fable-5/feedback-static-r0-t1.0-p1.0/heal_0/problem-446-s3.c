#include <stdio.h>
#include <stdlib.h>

int count_occurrences(const int *tuple, size_t tuple_size, const int *list, size_t list_size)
{
    int count = 0;
    size_t i;
    size_t j;

    if (tuple == NULL || list == NULL) {
        return -1;
    }

    for (i = 0; i < tuple_size; i++) {
        for (j = 0; j < list_size; j++) {
            if (tuple[i] == list[j]) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main(void)
{
    int tuple[] = {1, 2, 3, 4, 5, 2, 3, 2, 7, 8};
    int list[] = {2, 3, 9};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    size_t list_size = sizeof(list) / sizeof(list[0]);
    int result;

    result = count_occurrences(tuple, tuple_size, list, list_size);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Count of occurrences: %d\n", result);

    return EXIT_SUCCESS;
}