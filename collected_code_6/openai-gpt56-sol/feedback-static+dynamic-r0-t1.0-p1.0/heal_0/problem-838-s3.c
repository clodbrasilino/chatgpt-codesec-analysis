#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int minimum_swaps(const char *first, const char *second, size_t length)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return -1;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++mismatches_01;
        } else if (first[i] == '1' && second[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10 || mismatches_01 > (size_t)INT_MAX) {
        return -1;
    }

    return (int)mismatches_01;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t capacity = 1024;
    int result = EXIT_FAILURE;

    first = malloc(capacity);
    second = malloc(capacity);

    if (first == NULL || second == NULL) {
        goto cleanup;
    }

    if (scanf("%1023s %1023s", first, second) != 2) {
        goto cleanup;
    }

    size_t first_length = strlen(first);
    size_t second_length = strlen(second);

    if (first_length != second_length) {
        puts("-1");
        result = EXIT_SUCCESS;
        goto cleanup;
    }

    printf("%d\n", minimum_swaps(first, second, first_length));
    result = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return result;
}