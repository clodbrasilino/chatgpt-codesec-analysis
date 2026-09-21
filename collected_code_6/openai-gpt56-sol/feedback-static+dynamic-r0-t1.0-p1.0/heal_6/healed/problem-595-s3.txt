#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LENGTH ((size_t)100000)

static int minimum_swaps(const char *source, const char *target,
                         size_t length, size_t *result)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;
    size_t i;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
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

static int is_space_character(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int read_binary_string(char **output, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int c;
    int too_long = 0;
    int invalid = 0;

    if (output == NULL || length == NULL) {
        return -1;
    }

    *output = NULL;
    *length = 0;

    do {
        c = getchar();
        if (c == EOF) {
            return -1;
        }
    } while (is_space_character(c));

    buffer = malloc(MAX_LENGTH + 1);
    if (buffer == NULL) {
        return -1;
    }

    while (c != EOF && !is_space_character(c)) {
        if (c != '0' && c != '1') {
            invalid = 1;
        } else if (used < MAX_LENGTH) {
            buffer[used++] = (char)c;
        } else {
            too_long = 1;
        }

        c = getchar();
    }

    if (c == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (invalid || too_long || used == 0) {
        free(buffer);
        return -1;
    }

    buffer[used] = '\0';
    *output = buffer;
    *length = used;
    return 0;
}

static int only_trailing_whitespace(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (!is_space_character(c)) {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 1;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int status;
    int trailing_status;

    if (read_binary_string(&source, &source_length) != 0 ||
        read_binary_string(&target, &target_length) != 0) {
        free(source);
        free(target);
        fputs("Failed to read two binary strings.\n", stderr);
        return EXIT_FAILURE;
    }

    trailing_status = only_trailing_whitespace();
    if (trailing_status <= 0) {
        free(source);
        free(target);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (source_length != target_length) {
        free(source);
        free(target);
        puts("-1");
        return EXIT_SUCCESS;
    }

    status = minimum_swaps(source, target, source_length, &swaps);

    free(source);
    free(target);

    if (status < 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    return EXIT_SUCCESS;
}