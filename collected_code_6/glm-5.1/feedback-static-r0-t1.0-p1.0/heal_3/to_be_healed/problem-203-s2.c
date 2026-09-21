#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

int hamming_distance(int x, int y) {
    unsigned int xor_val = (unsigned int)x ^ (unsigned int)y;
    int distance = 0;
    while (xor_val) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    return distance;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(argv[0]);
        if (len > 1023) {
            len = 1023;
        }
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buf[1024];
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buf, argv[0], len);
        buf[len] = '\0';
        fprintf(stderr, "Usage: %s <int1> <int2>\n", buf);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     */
    if (errno != 0 || *endptr1 != '\0' || argv[1][0] == '\0' || *endptr2 != '\0' || argv[2][0] == '\0') {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Integer overflow\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", hamming_distance((int)val1, (int)val2));

    return EXIT_SUCCESS;
}