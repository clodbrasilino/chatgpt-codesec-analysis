#include <ctype.h>
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

static bool read_number(intmax_t *number)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (number == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return false;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] != '\n' && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return false;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    }

    char *end;
    errno = 0;
    intmax_t value = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *number = value;
    return true;
}

int main(void)
{
    intmax_t number;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               is_difference_of_two_squares(number) ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}