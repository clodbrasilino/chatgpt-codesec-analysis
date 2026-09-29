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

        if (sum > number - divisor) {
            return true;
        }

        sum += divisor;

        if (paired_divisor != divisor) {
            if (sum > number - paired_divisor) {
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char chunk[256];

        if (fgets(chunk, sizeof chunk, stream) == NULL) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (length == 0U) {
                free(buffer);
                errno = ENODATA;
                return NULL;
            }

            break;
        }

        size_t chunk_length = 0U;

        while (chunk[chunk_length] != '\0' &&
               chunk[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1U) {
            free(buffer);
            errno = EOVERFLOW;
            return NULL;
        }

        size_t required = length + chunk_length + 1U;

        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2U;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        for (size_t i = 0U; i < chunk_length; ++i) {
            buffer[length + i] = chunk[i];
        }

        length += chunk_length;

        if (chunk[chunk_length] == '\n') {
            break;
        }
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