#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 30
  *  test case 1 failed: expected 2, got 31
  *  test case 0 failed: expected 1, got 31
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
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (val > UINT_MAX || *endptr != '\0') {
        fprintf(stderr, "Error: Input out of unsigned int range or invalid\n");
        return EXIT_FAILURE;
    }
    unsigned int num = (unsigned int)val;
    int result = count_unset_bits(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}