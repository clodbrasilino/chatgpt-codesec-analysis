#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static bool is_abundant(unsigned long long number)
{
    if (number < 12ULL) {
        return false;
    }

    unsigned long long sum = 1ULL;

    for (unsigned long long divisor = 2ULL;
         divisor <= number / divisor;
         ++divisor) {
        if (number % divisor == 0ULL) {
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
    }

    return sum > number;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1U >= capacity) {
        size_t new_capacity = capacity == 0U ? 2U : capacity + 1U;
        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
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