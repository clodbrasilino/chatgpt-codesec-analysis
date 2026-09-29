#include <ctype.h>
#include <errno.h>
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
        int digit = *begin - '0';

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
    char input[1024];
    char *end;
    char *p;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    p = input;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    errno = 0;
    (void)strtoll(p, &end, 10);

    if (errno == ERANGE || end == p) {
        return EXIT_FAILURE;
    }

    p = end;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p != '\0') {
        return EXIT_FAILURE;
    }

    if (p == input + sizeof input - 1 && input[sizeof input - 2] != '\n') {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    printf("%d\n", digit_sum_difference(
        input + strspn(input, " \t\n\r\f\v"), end));

    return EXIT_SUCCESS;
}