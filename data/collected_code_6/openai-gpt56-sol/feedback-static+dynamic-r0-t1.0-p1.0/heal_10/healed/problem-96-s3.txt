#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_divisors(uint64_t value)
{
    uint64_t count = 0;

    for (uint64_t divisor = 1; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) {
            count += divisor == value / divisor ? UINT64_C(1) : UINT64_C(2);
        }
    }

    return count;
}

static int read_input(char **input)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (input == NULL) {
        return -1;
    }

    *input = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    *input = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (read_input(&input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    result = count_divisors((uint64_t)parsed);
    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}