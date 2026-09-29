#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strchr'
 */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *start;
    char *end;
    unsigned long long number;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (!feof(stdin)) {
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strlen'
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         */
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