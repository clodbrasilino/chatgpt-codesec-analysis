#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

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
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && length == 0U) {
                free(input);
                return NULL;
            }
            break;
        }

        if (length == capacity - 1U) {
            if (capacity > SIZE_MAX / 2U) {
                free(input);
                errno = EOVERFLOW;
                return NULL;
            }

            size_t new_capacity = capacity * 2U;
            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
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