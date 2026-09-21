#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

uint64_t countSetBits(uint64_t n) {
    if (n == 0) return 0;
    
    uint64_t x = n;
    int highestBit = 0;
    while (x >>= 1) highestBit++;
    
    uint64_t power = 1ULL << highestBit;
    uint64_t remainder = n - power;
    
    uint64_t count = (uint64_t)highestBit * (power >> 1) + remainder + 1;
    if (remainder > 0) {
        count += countSetBits(remainder);
    }
    
    return count;
}

int main(void) {
    uint64_t n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    char *endptr;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'strtoull'
     *  call to undeclared library function 'strtoull' with type 'unsigned long long (const char *, char **, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strtoull'; did you mean 'strtoumax'? [-Wimplicit-function-declaration]
     */
    n = strtoull(buffer, &endptr, 10);
    if (*endptr != '\0' && *endptr != '\n') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'errno' undeclared (first use in this function)
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     */
    if (n == UINT64_MAX && errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint64_t result = countSetBits(n);
    printf("Total set bits from 1 to %" PRIu64 ": %" PRIu64 "\n", n, result);
    
    return 0;
}