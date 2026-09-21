#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin]) != 0) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1U]) != 0) {
        --end;
    }

    if (begin == end) {
        return 0;
    }

    if (end - begin >= 2U &&
        hex[begin] == '0' &&
        (hex[begin + 1U] == 'x' || hex[begin + 1U] == 'X')) {
        begin += 2U;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (isxdigit((unsigned char)hex[i]) == 0) {
            return 0;
        }
    }

    last = (unsigned char)hex[end - 1U];
    *is_even = last == (unsigned char)'0' ||
               last == (unsigned char)'2' ||
               last == (unsigned char)'4' ||
               last == (unsigned char)'6' ||
               last == (unsigned char)'8' ||
               last == (unsigned char)'A' ||
               last == (unsigned char)'C' ||
               last == (unsigned char)'E' ||
               last == (unsigned char)'a' ||
               last == (unsigned char)'c' ||
               last == (unsigned char)'e';

    return 1;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0U;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return 1;
            }
            ++i;
        }
    }

    return ferror(stdin) == 0;
}

static int read_input(char **input, size_t *length)
{
    char *buffer;
    size_t used = 0U;

    if (input == NULL || length == NULL) {
        return -1;
    }

    *input = NULL;
    *length = 0U;

    buffer = malloc(INPUT_CAPACITY + 2U);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)(INPUT_CAPACITY + 2U), stdin) == NULL) {
        free(buffer);
        return ferror(stdin) != 0 ? -1 : 0;
    }

    while (buffer[used] != '\0' && buffer[used] != '\n') {
        ++used;
    }

    if (buffer[used] == '\n') {
        buffer[used] = '\0';
    } else if (used > INPUT_CAPACITY) {
        free(buffer);
        return discard_line() ? 0 : -1;
    } else if (used == INPUT_CAPACITY) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next == EOF) {
            if (ferror(stdin) != 0) {
                free(buffer);
                return -1;
            }
        } else if (next != '\n') {
            free(buffer);
            return discard_line() ? 0 : -1;
        }
    }

    *input = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    int is_even = 0;
    int status = read_input(&input, &length);

    if (status < 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_hex_even(input, length, &is_even) == 0) {
        free(input);
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(is_even != 0 ? "Even" : "Odd");
    return EXIT_SUCCESS;
}