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
        errno = ENOMEM;
        return NULL;
    }

    for (;;) {
        if (length + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(input);
                errno = EOVERFLOW;
                return NULL;
            }

            size_t new_capacity = capacity * 2U;
            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                int saved_errno = errno;
                free(input);
                errno = saved_errno != 0 ? saved_errno : ENOMEM;
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        if (fgets(input + length, (int)(capacity - length), stdin) == NULL) {
            if (ferror(stdin)) {
                int saved_errno = errno;
                free(input);
                errno = saved_errno != 0 ? saved_errno : EIO;
                return NULL;
            }

            if (length == 0U) {
                free(input);
                errno = 0;
                return NULL;
            }

            input[length] = '\0';
            return input;
        }

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
            return input;
        }

        if (feof(stdin)) {
            return input;
        }
    }
}

int main(void)
{
    errno = 0;
    char *input = read_line();

    if (input == NULL) {
        if (errno == EOVERFLOW) {
            fputs("Input is too large.\n", stderr);
        } else if (errno == 0) {
            fputs("No input provided.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }

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