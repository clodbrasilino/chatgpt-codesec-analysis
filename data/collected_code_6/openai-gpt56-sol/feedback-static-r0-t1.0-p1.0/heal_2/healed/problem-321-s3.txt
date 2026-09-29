#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

static int is_demlo_number(unsigned long long number)
{
    unsigned long long square = 0;
    unsigned long long increment = 1;

    while (square < number) {
        if (square > ULLONG_MAX - increment) {
            return 0;
        }

        square += increment;

        if (square < number) {
            if (increment > ULLONG_MAX - 2ULL) {
                return 0;
            }
            increment += 2ULL;
        }
    }

    if (square != number) {
        return 0;
    }

    do {
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
    } while (number % 10ULL == 1ULL);

    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long number;
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\0') {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_demlo_number(number) ? "Demlo number" : "Not a Demlo number");

    return EXIT_SUCCESS;
}