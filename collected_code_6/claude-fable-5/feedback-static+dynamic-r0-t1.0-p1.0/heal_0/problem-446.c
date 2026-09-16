#include <stdio.h>
#include <stdlib.h>

size_t count_occurrences(const int *tuple, size_t tuple_len,
                         const int *list, size_t list_len)
{
    size_t count = 0;
    size_t i;
    size_t j;

    if (tuple == NULL || list == NULL) {
        return 0;
    }

    for (i = 0; i < tuple_len; i++) {
        for (j = 0; j < list_len; j++) {
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
    const int tuple[] = {1, 2, 3, 4, 5, 2, 3, 2, 6, 7};
    const int list[] = {2, 3, 7};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    size_t list_len = sizeof(list) / sizeof(list[0]);
    size_t result;

    result = count_occurrences(tuple, tuple_len, list, list_len);

    if (printf("Count of occurrences: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}