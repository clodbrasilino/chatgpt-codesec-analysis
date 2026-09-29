#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    for (uint32_t mask = UINT32_C(1) << 31; mask != 0; mask >>= 1) {
        if ((value & mask) == 0) {
            return value | mask;
        }
    }

    return value;
}

static int read_input(char **buffer)
{
    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    size_t capacity = 32;
    size_t length = 0;
    char *data = malloc(capacity);

    if (data == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(data);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_data = realloc(data, new_capacity);

            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (char)ch;
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

int main(void)
{
    char *input = NULL;

    if (!read_input(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *start = input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint32_t result = set_leftmost_unset_bit((uint32_t)parsed);
    free(input);

    if (printf("%" PRIu32 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}