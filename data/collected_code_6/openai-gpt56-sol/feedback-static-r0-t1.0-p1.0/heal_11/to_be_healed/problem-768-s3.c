#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

static int has_odd_parity(uintmax_t value)
{
    int parity = 0;

    while (value != UINTMAX_C(0)) {
        parity ^= 1;
        value &= value - UINTMAX_C(1);
    }

    return parity;
}

int main(void)
{
    uintmax_t value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= sizeof input) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            }
            return EXIT_FAILURE;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strtoumax'; did you mean 'strtouq'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'strtoumax'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    value = strtoumax(input, &end, 0);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}