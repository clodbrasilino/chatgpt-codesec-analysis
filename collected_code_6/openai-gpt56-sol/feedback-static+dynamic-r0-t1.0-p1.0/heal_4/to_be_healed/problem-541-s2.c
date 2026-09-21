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

        if (sum > number) {
            return true;
        }
    }

    return sum > number;
}

static char *read_line(void)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *input = malloc(capacity);

    if (input == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[4096];

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                return NULL;
            }

            if (length == 0U) {
                free(input);
                errno = 0;
                return NULL;
            }

            break;
        }

        size_t chunk_length = 0U;

        while (buffer[chunk_length] != '\0' &&
               buffer[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1U) {
            free(input);
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

            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        for (size_t i = 0U; i < chunk_length; ++i) {
            input[length + i] = buffer[i];
        }

        length += chunk_length;

        if (buffer[chunk_length] == '\n') {
            break;
        }
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    errno = 0;
    char *input = read_line();

    if (input == NULL) {
        fputs(errno == EOVERFLOW
                  ? "Input is too large.\n"
                  : "Failed to read input.\n",
              stderr);
        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
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

    while (isspace((unsigned char)*end)) {
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