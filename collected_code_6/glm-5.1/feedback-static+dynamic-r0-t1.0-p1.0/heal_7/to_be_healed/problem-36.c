#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isdigit'
  */

long long find_nth_digit(long long numerator, long long denominator, long long n) {
    if (denominator <= 0 || n <= 0) {
        return -1;
    }
    if (numerator < 0) {
        numerator = -numerator;
    }
    long long remainder = numerator % denominator;
    for (long long i = 0; i < n; ++i) {
        if (remainder > LLONG_MAX / 10) {
            return -1;
        }
        remainder *= 10;
        long long digit = remainder / denominator;
        remainder %= denominator;
        if (i == n - 1) {
            return digit;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char *endptr1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(argv[1]);
    /* Possible weaknesses found:
     *  include the header <ctype.h> or explicitly provide a declaration for 'isdigit'
     *  call to undeclared library function 'isdigit' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
     */
    if (len1 == 0 || (len1 > 1 && argv[1][0] == '-' && !isdigit((unsigned char)argv[1][1]))) {
        return EXIT_FAILURE;
    }
    long long numerator = strtoll(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0') {
        return EXIT_FAILURE;
    }
    
    char *endptr2;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(argv[2]);
    if (len2 == 0 || (len2 > 1 && argv[2][0] == '-' && !isdigit((unsigned char)argv[2][1]))) {
        return EXIT_FAILURE;
    }
    long long denominator = strtoll(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0') {
        return EXIT_FAILURE;
    }
    
    char *endptr3;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len3 = strlen(argv[3]);
    if (len3 == 0 || (len3 > 1 && argv[3][0] == '-' && !isdigit((unsigned char)argv[3][1]))) {
        return EXIT_FAILURE;
    }
    long long n = strtoll(argv[3], &endptr3, 10);
    if (errno != 0 || *endptr3 != '\0') {
        return EXIT_FAILURE;
    }
    
    long long result = find_nth_digit(numerator, denominator, n);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}