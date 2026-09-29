#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 30
  *  test case 1 failed: expected 2, got 31
  *  test case 0 failed: expected 1, got 31
  */

int count_unset_bits(int n) {
    int count = 0;
    int bits = sizeof(n) * CHAR_BIT;
    unsigned int un = (unsigned int)n;
    for (int i = 0; i < bits; i++) {
        if (!(un & 1)) {
            count++;
        }
        un >>= 1;
    }
    return count;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (val > INT_MAX || val < INT_MIN || *endptr != '\0') {
        fprintf(stderr, "Error: Input out of int range or invalid\n");
        return EXIT_FAILURE;
    }
    int num = (int)val;
    int result = count_unset_bits(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}