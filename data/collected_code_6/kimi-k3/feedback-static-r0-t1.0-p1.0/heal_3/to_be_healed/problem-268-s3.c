#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

long long star_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return 6LL * n * (n - 1) + 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    unsigned int n;
    long long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    len = strlen(buffer);
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Error: input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || val < 0 || val > UINT_MAX) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)val;

    if (n > 0 && n > (ULLONG_MAX - 1) / 6 / (n - 1)) {
        fprintf(stderr, "Input too large: would cause overflow\n");
        return EXIT_FAILURE;
    }

    result = star_number(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}