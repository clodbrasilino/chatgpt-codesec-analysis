#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int minimum_swaps(const char *source, const char *target, size_t *result)
{
    size_t length;
    size_t source_ones = 0;
    size_t target_ones = 0;
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    length = strlen(source);

    if (length != strlen(target)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return -1;
        }

        source_ones += source[i] == '1';
        target_ones += target[i] == '1';

        if (source[i] == '0' && target[i] == '1') {
            ++mismatches_01;
        } else if (source[i] == '1' && target[i] == '0') {
            ++mismatches_10;
        }
    }

    if (source_ones != target_ones || mismatches_01 != mismatches_10) {
        return 1;
    }

    *result = mismatches_01;
    return 0;
}

int main(void)
{
    char source[100001];
    char target[100001];
    size_t swaps;
    int status;

    if (scanf("%100000s %100000s", source, target) != 2) {
        fprintf(stderr, "Failed to read two binary strings.\n");
        return EXIT_FAILURE;
    }

    status = minimum_swaps(source, target, &swaps);

    if (status < 0) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (status > 0) {
        printf("-1\n");
    } else {
        printf("%zu\n", swaps);
    }

    return EXIT_SUCCESS;
}