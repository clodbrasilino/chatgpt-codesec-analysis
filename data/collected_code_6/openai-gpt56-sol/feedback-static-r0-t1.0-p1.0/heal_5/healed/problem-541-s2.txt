#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

static bool is_abundant(unsigned long long number)
{
    if (number < 12ULL) {
        return false;
    }

    unsigned long long sum = 1ULL;

    for (unsigned long long divisor = 2ULL;
         divisor <= number / divisor;
         ++divisor) {
        if (number % divisor != 0ULL) {
            continue;
        }

        unsigned long long paired_divisor = number / divisor;

        if (divisor > number - sum) {
            return true;
        }
        sum += divisor;

        if (paired_divisor != divisor) {
            if (paired_divisor > number - sum) {
                return true;
            }
            sum += paired_divisor;
        }
    }

    return sum > number;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (length == 0U) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1U) {
            free(buffer);
            errno = EOVERFLOW;
            return NULL;
        }

        if (length + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                errno = EOVERFLOW;
                return NULL;
            }

            size_t new_capacity = capacity * 2U;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    errno = 0;
    char *input = read_line(stdin);

    if (input == NULL) {
        if (errno == EOVERFLOW) {
            fputs("Input is too long.\n", stderr);
        } else if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Failed to read or allocate input.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(is_abundant(number) ? "Abundant" : "Not abundant");

    return EXIT_SUCCESS;
}