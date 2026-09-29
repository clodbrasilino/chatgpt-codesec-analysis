#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int count_unset_bits(unsigned int n) {
    int count = 0;
    unsigned int temp = n;
    while (temp) {
        if ((temp & 1) == 0) {
            count++;
        }
        temp >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    unsigned int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unsigned_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long parsed = strtoul(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || parsed > UINT_MAX) {
        fprintf(stderr, "Error: Invalid input or number out of range for unsigned int.\n");
        return EXIT_FAILURE;
    }
    num = (unsigned int)parsed;

    int result = count_unset_bits(num);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}