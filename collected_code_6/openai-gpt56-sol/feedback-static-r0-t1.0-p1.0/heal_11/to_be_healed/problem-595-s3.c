#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LENGTH ((size_t)100000)

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

static int is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int discard_token(int ch)
{
    while (ch != EOF && !is_space_character(ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_binary_string(char **string, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int ch;

    if (string == NULL || length == NULL) {
        return -1;
    }

    *string = NULL;
    *length = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (is_space_character(ch));

    buffer = malloc(MAX_LENGTH + 1);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !is_space_character(ch)) {
        if (ch != '0' && ch != '1') {
            (void)discard_token(ch);
            free(buffer);
            return -1;
        }

        if (used == MAX_LENGTH) {
            (void)discard_token(ch);
            free(buffer);
            return -1;
        }

        buffer[used++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
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
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int status;

    if (read_binary_string(&source, &source_length) != 0 ||
        read_binary_string(&target, &target_length) != 0) {
        free(source);
        free(target);
        fputs("Failed to read two valid binary strings.\n", stderr);
        return EXIT_FAILURE;
    }

    status = minimum_swaps(source, source_length,
                           target, target_length, &swaps);

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