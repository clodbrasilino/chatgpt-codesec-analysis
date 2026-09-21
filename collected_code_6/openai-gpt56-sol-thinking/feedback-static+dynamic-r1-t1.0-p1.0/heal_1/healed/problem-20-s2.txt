#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\0') {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

static bool is_woodall(uint64_t number)
{
    uint64_t power = 2;

    if (number == 0) {
        return false;
    }

    for (uint64_t index = 1; ; ++index) {
        if (index > UINT64_MAX / power) {
            return false;
        }

        uint64_t candidate = index * power - 1;

        if (candidate == number) {
            return true;
        }

        if (candidate > number || power > UINT64_MAX / 2) {
            return false;
        }

        power *= 2;
    }
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    uint64_t number = (uint64_t)value;

    printf("%s\n", is_woodall(number)
                       ? "Woodall number"
                       : "Not a Woodall number");

    free(input);
    return EXIT_SUCCESS;
}