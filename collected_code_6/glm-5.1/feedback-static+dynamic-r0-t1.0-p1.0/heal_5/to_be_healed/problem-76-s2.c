#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

unsigned long long count_squares(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    
    unsigned int min = m < n ? m : n;
    unsigned int max = m < n ? n : m;
    
    unsigned long long count = 0;
    
    for (unsigned int i = 1; i <= min; i++) {
        count += (unsigned long long)(max - i + 1) * (min - i + 1);
    }
    
    return count;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[static 3]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <m> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    char *endptr2;
    unsigned long val1 = strtoul(argv[1], &endptr1, 10);
    unsigned long val2 = strtoul(argv[2], &endptr2, 10);
    
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 > 4294967295UL || val2 > 4294967295UL) {
        fprintf(stderr, "Error: Arguments must be non-negative integers.\n");
        return EXIT_FAILURE;
    }
    
    unsigned int m = (unsigned int)val1;
    unsigned int n = (unsigned int)val2;
    
    printf("%llu\n", count_squares(m, n));
    fflush(stdout);
    
    return EXIT_SUCCESS;
}