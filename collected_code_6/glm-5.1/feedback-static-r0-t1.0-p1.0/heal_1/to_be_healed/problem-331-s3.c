#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int count_unset_bits(unsigned int n) {
    int count = 0;
    for (int i = 0; i < (int)(sizeof(n) * 8); i++) {
        if (!(n & 1)) {
            count++;
        }
        n >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned long val = strtoul(argv[1], NULL, 10);
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     */
    if (val > UINT_MAX) {
        fprintf(stderr, "Error: Input out of unsigned int range\n");
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int result = count_unset_bits(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}