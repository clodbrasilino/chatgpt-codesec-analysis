#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

uint64_t decagonal_number(uint64_t n) {
    return 4 * n * n - 3 * n;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    uint64_t n;

    printf("Enter the value of n: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (buffer[sizeof(buffer) - 1] != '\0' && strchr(buffer, '\n') == NULL) {
        fprintf(stderr, "Error: Input too long.\n");
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (endptr == buffer) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Error: Invalid input. Please enter only a positive integer.\n");
        return 1;
    }

    if (n > 2147483647ULL) {
        fprintf(stderr, "Error: Input too large. Maximum value is 2147483647.\n");
        return 1;
    }

    uint64_t decagonal = decagonal_number(n);
    printf("The %" PRIu64 "th decagonal number is: %" PRIu64 "\n", n, decagonal);

    return 0;
}