#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

int last_digit(long long number)
{
    int digit = (int)(number % 10);
    return digit < 0 ? -digit : digit;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    long long number;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] == '\0') {
        return EXIT_FAILURE;
    }

    if (input[sizeof input - 2] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        for (ch = getchar(); ch != '\n' && ch != EOF; ch++) {
        }

        if (ch != EOF || input[sizeof input - 2] != '\0') {
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        end++;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%d\n", last_digit(number));
    return EXIT_SUCCESS;
}