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
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation failed.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
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
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

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