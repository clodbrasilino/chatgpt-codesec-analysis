#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(intmax_t number)
{
    intmax_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    intmax_t number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *newline = NULL;

    for (char *p = input; *p != '\0'; ++p) {
        if (*p == '\n') {
            newline = p;
            break;
        }
    }

    if (newline == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               is_difference_of_two_squares(number) ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}