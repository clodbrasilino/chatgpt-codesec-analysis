#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

static int is_demlo_number(unsigned long long number)
{
    unsigned long long low = 0;
    unsigned long long high = number < 0xffffffffULL
                            ? number
                            : 0xffffffffULL;

    while (low <= high) {
        unsigned long long root = low + (high - low) / 2;

        if (root != 0 && root > number / root) {
            high = root - 1;
        } else {
            unsigned long long square = root * root;

            if (square == number) {
                break;
            }

            low = root + 1;
        }
    }

    if (low > high) {
        return 0;
    }

    for (;;) {
        if (number % 10ULL != 1ULL) {
            return 0;
        }

        number /= 10ULL;

        if (number == 0ULL) {
            return 1;
        }

        while (number % 10ULL == 2ULL) {
            number /= 10ULL;
        }

        if (number == 0ULL) {
            return 0;
        }
    }
}

int main(void)
{
    char input[128];
    char *start;
    char *end;
    unsigned long long number;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (!feof(stdin)) {
            return EXIT_FAILURE;
        }

        if (strlen(input) == sizeof input - 1) {
            return EXIT_FAILURE;
        }
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_demlo_number(number) ? "Demlo number" : "Not a Demlo number");
    return EXIT_SUCCESS;
}