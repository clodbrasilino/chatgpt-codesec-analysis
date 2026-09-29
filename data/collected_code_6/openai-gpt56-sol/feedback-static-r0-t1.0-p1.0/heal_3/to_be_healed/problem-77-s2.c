#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *begin, const char *end)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    while (begin < end) {
        int digit = (unsigned char)*begin - '0';

        if ((digit % 2) == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }

        ++begin;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    const char *begin;
    const char *end;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *temporary;

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > (size_t)-1 / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
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

    {
        const char *number_end = end;

        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end != '\0') {
            free(input);
            return EXIT_FAILURE;
        }

        printf("%d\n", digit_sum_difference(begin, number_end));
    }

    free(input);
    return EXIT_SUCCESS;
}