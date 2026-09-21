#include <limits.h>
#include <stddef.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static int count_character_frequency(const char *string,
                                     size_t frequencies[UCHAR_MAX + 1])
{
    const unsigned char *current;

    if (string == NULL || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        frequencies[i] = 0;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'SIZE_MAX'
         *  'SIZE_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (frequencies[*current] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[*current];
        ++current;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t frequencies[UCHAR_MAX + 1];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        input[0] = '\0';
    }

    if (count_character_frequency(input, frequencies) != 0) {
        return 1;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] != 0) {
            if (printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}