#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *begin, const char *end, int *result)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    while (begin < end) {
        int digit = *begin - '0';

        if ((digit % 2) == 0) {
            if (even_sum > INT_MAX - digit) {
                return 0;
            }
            even_sum += digit;
        } else {
            if (odd_sum > INT_MAX - digit) {
                return 0;
            }
            odd_sum += digit;
        }

        ++begin;
    }

    *result = even_sum - odd_sum;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;
    int result;
    const char *begin;
    const char *end;
    const char *number_end;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_input;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    begin = input;
    while (isspace((unsigned char)*begin)) {
        ++begin;
    }

    end = begin;
    if (*end == '+' || *end == '-') {
        ++end;
    }

    {
        const char *digits = end;

        while (isdigit((unsigned char)*end)) {
            ++end;
        }

        if (end == digits) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    number_end = end;

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (!digit_sum_difference(begin, number_end, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(input);
    return EXIT_SUCCESS;
}