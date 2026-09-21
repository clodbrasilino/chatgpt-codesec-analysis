#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LENGTH 100000u

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
        return 1;
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

static int read_binary_string(char **string, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    int ch;

    if (string == NULL || length == NULL) {
        return -1;
    }

    do {
        ch = getchar();
    } while (ch != EOF && (ch == ' ' || ch == '\t' ||
                           ch == '\n' || ch == '\r' ||
                           ch == '\f' || ch == '\v'));

    if (ch == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && ch != ' ' && ch != '\t' &&
           ch != '\n' && ch != '\r' && ch != '\f' && ch != '\v') {
        if (ch != '0' && ch != '1') {
            free(buffer);
            return -1;
        }

        if (used >= MAX_LENGTH) {
            free(buffer);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized;

            if (new_capacity > MAX_LENGTH + 1) {
                new_capacity = MAX_LENGTH + 1;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
        ch = getchar();
    }

    if (used == 0) {
        free(buffer);
        return -1;
    }

    buffer[used] = '\0';
    *string = buffer;
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
        fprintf(stderr, "Failed to read two valid binary strings.\n");
        return EXIT_FAILURE;
    }

    status = minimum_swaps(source, source_length,
                           target, target_length, &swaps);

    free(source);
    free(target);

    if (status < 0) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (status > 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    return EXIT_SUCCESS;
}