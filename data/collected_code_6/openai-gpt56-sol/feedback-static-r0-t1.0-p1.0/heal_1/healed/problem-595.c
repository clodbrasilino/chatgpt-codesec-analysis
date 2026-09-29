#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int minimum_swaps(const char *source, size_t source_length,
                         const char *target, size_t target_length,
                         size_t *result)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

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

        if (source[i] == '0' && target[i] == '1') {
            ++mismatches_01;
        } else if (source[i] == '1' && target[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10) {
        return 1;
    }

    *result = mismatches_01;
    return 0;
}

static size_t remove_line_ending(char *line, size_t length)
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
    size_t swaps = 0;
    ssize_t source_read;
    ssize_t target_read;
    int status;
    int exit_code = EXIT_FAILURE;

    source_read = getline(&source, &source_capacity, stdin);
    if (source_read < 0) {
        goto cleanup;
    }

    target_read = getline(&target, &target_capacity, stdin);
    if (target_read < 0) {
        goto cleanup;
    }

    source_length = remove_line_ending(source, (size_t)source_read);
    target_length = remove_line_ending(target, (size_t)target_read);

    status = minimum_swaps(source, source_length, target, target_length, &swaps);

    if (status == 0) {
        if (printf("%zu\n", swaps) < 0) {
            goto cleanup;
        }
        exit_code = EXIT_SUCCESS;
    } else if (status == 1) {
        if (printf("-1\n") < 0) {
            goto cleanup;
        }
        exit_code = EXIT_SUCCESS;
    }

cleanup:
    free(source);
    free(target);
    return exit_code;
}