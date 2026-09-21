#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int minimum_swaps(const char *source, size_t source_length,
                         const char *target, size_t target_length,
                         size_t *result)
{
    size_t source_ones = 0;
    size_t target_ones = 0;
    size_t mismatches = 0;

    if (source == NULL || target == NULL || result == NULL ||
        source_length != target_length) {
        return -1;
    }

    for (size_t i = 0; i < source_length; ++i) {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return -1;
        }

        source_ones += source[i] == '1';
        target_ones += target[i] == '1';
        mismatches += source[i] != target[i];
    }

    if (source_ones != target_ones) {
        return -1;
    }

    *result = mismatches / 2;
    return 0;
}

static size_t trim_line_ending(char *line, size_t length)
{
    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    return length;
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
    ssize_t source_read;
    ssize_t target_read;
    int status = EXIT_FAILURE;

    source_read = getline(&source, &source_capacity, stdin);
    if (source_read < 0) {
        goto cleanup;
    }

    target_read = getline(&target, &target_capacity, stdin);
    if (target_read < 0) {
        goto cleanup;
    }

    source_length = trim_line_ending(source, (size_t)source_read);
    target_length = trim_line_ending(target, (size_t)target_read);

    if (minimum_swaps(source, source_length, target, target_length,
                      &swaps) != 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    status = EXIT_SUCCESS;

cleanup:
    free(source);
    free(target);
    return status;
}