#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  */

unsigned long long count_squares(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    unsigned long long count = 0;
    unsigned int min = m < n ? m : n;
    for (unsigned int i = 1; i <= min; i++) {
        count += (unsigned long long)(m - i + 1) * (n - i + 1);
    }
    return count;
}

int main(int argc, char * const * argv) {
    unsigned long long m, n;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <m> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t len1 = strnlen(argv[1], 11);
    size_t len2 = strnlen(argv[2], 11);
    if (len1 == 0 || len1 > 10 || len2 == 0 || len2 > 10) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    char *end1;
    char *end2;
    errno = 0;
    m = strtoull(argv[1], &end1, 10);
    errno = 0;
    n = strtoull(argv[2], &end2, 10);
    if (*end1 != '\0' || *end2 != '\0' || m > 4294967295ULL || n > 4294967295ULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%llu\n", count_squares((unsigned int)m, (unsigned int)n));
    return EXIT_SUCCESS;
}