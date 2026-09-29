#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_inner_bits(uint32_t value)
{
    if (value <= UINT32_C(1)) {
        return value;
    }

    uint32_t highest_bit = UINT32_C(1);

    while (highest_bit <= value / UINT32_C(2)) {
        highest_bit <<= 1;
    }

    return value ^ (highest_bit - UINT32_C(2));
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT32_MAX) {
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

    free(input);

    if (printf("%" PRIu32 "\n", toggle_inner_bits((uint32_t)parsed)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}