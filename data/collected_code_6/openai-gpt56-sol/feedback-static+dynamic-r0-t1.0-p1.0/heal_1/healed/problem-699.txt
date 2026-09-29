#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int minimum_swaps(const char *source, size_t source_length,
                  const char *target, size_t target_length,
                  size_t *result)
{
    size_t source_ones = 0;
    size_t target_ones = 0;
    size_t mismatches = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    if (source_length != target_length) {
        return -1;
    }

    for (size_t i = 0; i < source_length; ++i) {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return -1;
        }

        if (source[i] == '1') {
            ++source_ones;
        }

        if (target[i] == '1') {
            ++target_ones;
        }

        if (source[i] != target[i]) {
            ++mismatches;
        }
    }

    if (source_ones != target_ones) {
        return -1;
    }

    *result = mismatches / 2;
    return 0;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t source_capacity = 0;
    size_t target_capacity = 0;
    size_t source_length;
    size_t target_length;
    size_t swaps;
    ssize_t read_length;
    int status = EXIT_FAILURE;

    read_length = getline(&source, &source_capacity, stdin);
    if (read_length < 0) {
        goto cleanup;
    }
    source_length = (size_t)read_length;

    read_length = getline(&target, &target_capacity, stdin);
    if (read_length < 0) {
        goto cleanup;
    }
    target_length = (size_t)read_length;

    if (source_length > 0 && source[source_length - 1] == '\n') {
        --source_length;
    }
    if (source_length > 0 && source[source_length - 1] == '\r') {
        --source_length;
    }

    if (target_length > 0 && target[target_length - 1] == '\n') {
        --target_length;
    }
    if (target_length > 0 && target[target_length - 1] == '\r') {
        --target_length;
    }

    if (minimum_swaps(source, source_length, target, target_length,
                      &swaps) != 0) {
        if (puts("-1") == EOF) {
            goto cleanup;
        }
    } else if (printf("%zu\n", swaps) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(source);
    free(target);
    return status;
}