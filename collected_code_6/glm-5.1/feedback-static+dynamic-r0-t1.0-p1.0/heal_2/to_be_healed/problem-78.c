#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 2 failed: expected 8, got <no output>
  */

int count_odd_set_bits(int n) {
    if (n < 0) {
        return -1;
    }
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (__builtin_parity(i) != 0) {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = count_odd_set_bits(n);
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}