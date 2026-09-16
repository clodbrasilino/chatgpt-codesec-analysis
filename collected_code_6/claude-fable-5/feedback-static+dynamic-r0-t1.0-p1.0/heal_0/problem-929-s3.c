#include <stdio.h>
#include <stddef.h>

size_t count_repeated_items(const int *tuple, size_t length)
{
    size_t count = 0;
    size_t i;
    size_t j;

    if (tuple == NULL || length == 0) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        int seen_before = 0;
        for (j = 0; j < i; j++) {
            if (tuple[j] == tuple[i]) {
                seen_before = 1;
                break;
            }
        }
        if (seen_before) {
            continue;
        }
        {
            size_t occurrences = 1;
            for (j = i + 1; j < length; j++) {
                if (tuple[j] == tuple[i]) {
                    occurrences++;
                }
            }
            if (occurrences > 1) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    int tuple[] = {1, 2, 3, 2, 4, 1, 5, 1};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    size_t repeated;

    repeated = count_repeated_items(tuple, length);

    if (printf("Number of repeated items: %zu\n", repeated) < 0) {
        return 1;
    }

    return 0;
}