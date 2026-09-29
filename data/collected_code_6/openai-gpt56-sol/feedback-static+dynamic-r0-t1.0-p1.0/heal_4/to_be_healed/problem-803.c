#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

static bool is_perfect_square(uintmax_t number)
{
    uintmax_t left = 0;
    uintmax_t right = number;

    while (left <= right) {
        uintmax_t middle = left + (right - left) / 2;

        if (middle != 0 && middle > number / middle) {
            right = middle - 1;
        } else {
            uintmax_t square = middle * middle;

            if (square == number) {
                return true;
            }

            left = middle + 1;
        }
    }

    return false;
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

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
        }
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
    uintmax_t number = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_perfect_square(number) ? "True" : "False");

    return EXIT_SUCCESS;
}