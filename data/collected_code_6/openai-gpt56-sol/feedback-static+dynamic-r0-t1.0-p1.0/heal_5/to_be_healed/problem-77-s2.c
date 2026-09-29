#include <ctype.h>
#include <errno.h>
#include <stdint.h>
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

        if (digit % 2 == 0) {
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
    size_t capacity = 0;
    size_t length = 0;
    char *begin;
    char *end;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

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

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity < length + 1) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    begin = input;
    while (isspace((unsigned char)*begin)) {
        ++begin;
    }

    errno = 0;
    (void)strtoll(begin, &end, 10);

    if (errno == ERANGE || end == begin) {
        free(input);
        return EXIT_FAILURE;
    }

    {
        char *p = end;

        while (isspace((unsigned char)*p)) {
            ++p;
        }

        if (*p != '\0') {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (printf("%d\n", digit_sum_difference(begin, end)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}