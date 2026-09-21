#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ULLONG_DECIMAL_DIGITS \
    ((sizeof(unsigned long long) * CHAR_BIT * 30103ULL) / 100000ULL + 1ULL)

static bool is_keith_number(unsigned long long number)
{
    unsigned long long sequence[ULLONG_DECIMAL_DIGITS];
    unsigned long long value = number;
    size_t count = 0;
    size_t index = 0;

    if (number < 10ULL) {
        return false;
    }

    do {
        sequence[count++] = value % 10ULL;
        value /= 10ULL;
    } while (value != 0ULL);

    for (size_t i = 0; i < count / 2; ++i) {
        unsigned long long temporary = sequence[i];
        sequence[i] = sequence[count - i - 1];
        sequence[count - i - 1] = temporary;
    }

    for (;;) {
        unsigned long long sum = 0ULL;

        for (size_t i = 0; i < count; ++i) {
            if (sequence[i] > ULLONG_MAX - sum) {
                return false;
            }
            sum += sequence[i];
        }

        if (sum == number) {
            return true;
        }

        if (sum > number) {
            return false;
        }

        sequence[index] = sum;
        index = (index + 1U) % count;
    }
}

static bool read_line(FILE *stream, char **line)
{
    enum { INITIAL_CAPACITY = 64 };

    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;

    if (stream == NULL || line == NULL) {
        return false;
    }

    *line = NULL;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return false;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? INITIAL_CAPACITY : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            if (new_capacity < required) {
                free(buffer);
                return false;
            }

            char *temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return false;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return false;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long number;

    if (!read_line(stdin, &input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%llu is %sa Keith number.\n",
           number, is_keith_number(number) ? "" : "not ");

    free(input);
    return EXIT_SUCCESS;
}