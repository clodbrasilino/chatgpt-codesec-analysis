#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first = (unsigned int)(number % 10ULL);
    number /= 10ULL;

    if (number == 0ULL) {
        return false;
    }

    unsigned int second = (unsigned int)(number % 10ULL);
    number /= 10ULL;

    if (first == second) {
        return false;
    }

    bool expect_first = true;

    while (number != 0ULL) {
        unsigned int digit = (unsigned int)(number % 10ULL);

        if (digit != (expect_first ? first : second)) {
            return false;
        }

        expect_first = !expect_first;
        number /= 10ULL;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *newline = input;

    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline == '\n') {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    return EXIT_SUCCESS;
}