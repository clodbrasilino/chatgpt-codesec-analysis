#include <stdio.h>
#include <stddef.h>

size_t count_occurrences(const int *tuple, size_t length, int element)
{
    size_t count = 0;
    size_t i;

    if (tuple == NULL) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (tuple[i] == element) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int tuple[] = {3, 7, 3, 9, 3, 5, 7, 3};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    int target = 3;
    size_t result;

    result = count_occurrences(tuple, length, target);

    if (printf("Element %d occurs %zu times.\n", target, result) < 0) {
        return 1;
    }

    return 0;
}