#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_with_length(char *string, size_t k)
{
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    char *read;
    char *write;
    int has_word = 0;

    if (string == NULL) {
        return -1;
    }

    read = string;
    write = string;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        char *word_start;
        size_t word_length = 0;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (isspace((unsigned char)*read)) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ++read;
        }

        if (*read == '\0') {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        word_start = read;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (*read != '\0' && !isspace((unsigned char)*read)) {
            ++word_length;
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ++read;
        }

        if (word_length != k) {
            if (has_word) {
                *write++ = ' ';
            }

            memmove(write, word_start, word_length);
            write += word_length;
            has_word = 1;
        }
    }

    *write = '\0';
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end;
    char *input;
    const char *number;
    uintmax_t parsed;
    size_t total_length = 0;
    size_t position = 0;
    size_t k;
    int i;
    int result;

    if (argc < 3) {
        fputs("Usage: program k string\n", stderr);
        return EXIT_FAILURE;
    }

    number = argv[1];

    while (isspace((unsigned char)*number)) {
        ++number;
    }

    if (*number == '\0' || *number == '-') {
        fputs("Invalid word length\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(number, &end, 10);

    if (errno == ERANGE || end == number || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        fputs("Invalid word length\n", stderr);
        return EXIT_FAILURE;
    }

    k = (size_t)parsed;

    for (i = 2; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t argument_length = strlen(argv[i]);

        if (argument_length > SIZE_MAX - total_length) {
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }

        total_length += argument_length;

        if (i + 1 < argc) {
            if (total_length == SIZE_MAX) {
                fputs("Input is too large\n", stderr);
                return EXIT_FAILURE;
            }
            ++total_length;
        }
    }

    if (total_length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    input = malloc(total_length + 1);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 2; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t argument_length = strlen(argv[i]);

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input + position, argv[i], argument_length);
        position += argument_length;

        if (i + 1 < argc) {
            input[position++] = ' ';
        }
    }

    input[position] = '\0';

    if (remove_words_with_length(input, k) != 0) {
        free(input);
        fputs("Failed to process the string\n", stderr);
        return EXIT_FAILURE;
    }

    result = printf("%s\n", input);
    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}