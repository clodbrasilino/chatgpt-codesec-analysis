#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == UINT64_C(0)) {
        return UINT64_C(0);
    }

    uint64_t result = UINT64_C(1);

    while (number > UINT64_C(1)) {
        number >>= 1;
        result <<= 1;
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *end;
    errno = 0;
    uintmax_t value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", highest_power_of_two((uint64_t)value));
    return EXIT_SUCCESS;
}