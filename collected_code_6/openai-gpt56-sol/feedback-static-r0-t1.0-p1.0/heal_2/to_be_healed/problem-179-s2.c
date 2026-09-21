#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_keith_number(unsigned long long number)
{
    unsigned long long sequence[20] = {0};
    unsigned long long value = number;
    size_t count = 0;
    size_t index = 0;

    if (number < 10) {
        return false;
    }

    do {
        if (count >= sizeof sequence / sizeof sequence[0]) {
            return false;
        }

        sequence[count++] = value % 10;
        value /= 10;
    } while (value != 0);

    for (size_t i = 0; i < count / 2; ++i) {
        unsigned long long temporary = sequence[i];
        sequence[i] = sequence[count - i - 1];
        sequence[count - i - 1] = temporary;
    }

    for (;;) {
        unsigned long long sum = 0;

        for (size_t i = 0; i < count; ++i) {
            if (sequence[i] > ULLONG_MAX - sum) {
                return false;
            }

            sum += sequence[i];
        }

        if (sum == number) {
            return true;
        }

        if (sum > number) {
            return false;
        }

        sequence[index] = sum;
        index = (index + 1) % count;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128] = {0};
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] == '-') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%llu is %sa Keith number.\n",
           number, is_keith_number(number) ? "" : "not ");

    return EXIT_SUCCESS;
}