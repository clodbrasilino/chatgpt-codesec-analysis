#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LENGTH 100000U

static int minimum_swaps(const char *source, const char *target,
                         size_t length, size_t *result)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
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

static int read_binary_string(char **output, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;
    int c;

    if (output == NULL || length == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } while (c != EOF && (c == ' ' || c == '\t' || c == '\n' ||
                          c == '\r' || c == '\f' || c == '\v'));

    if (c == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (c != EOF && c != ' ' && c != '\t' && c != '\n' &&
           c != '\r' && c != '\f' && c != '\v') {
        char *resized;

        if (c != '0' && c != '1') {
            free(buffer);
            return -1;
        }

        if (used >= MAX_LENGTH) {
            free(buffer);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity = capacity * 2;

            if (new_capacity > MAX_LENGTH + 1U) {
                new_capacity = MAX_LENGTH + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    }

    if (used == 0) {
        free(buffer);
        return -1;
    }

    buffer[used] = '\0';
    *output = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t source_length;
    size_t target_length;
    size_t swaps;
    int status;

    if (read_binary_string(&source, &source_length) != 0 ||
        read_binary_string(&target, &target_length) != 0) {
        free(source);
        free(target);
        fprintf(stderr, "Failed to read two binary strings.\n");
        return EXIT_FAILURE;
    }

    if (source_length != target_length) {
        printf("-1\n");
        free(source);
        free(target);
        return EXIT_SUCCESS;
    }

    status = minimum_swaps(source, target, source_length, &swaps);

    free(source);
    free(target);

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