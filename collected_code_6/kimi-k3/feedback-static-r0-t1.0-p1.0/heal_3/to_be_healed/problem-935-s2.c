#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

static uint64_t sum_of_squares(uint64_t n)
{
    if (n == 0) {
        return 0;
    }
    
    if (n > 1862644) {
        errno = ERANGE;
        return UINT64_MAX;
    }
    
    return (n * (n + 1) * (2 * n + 1)) / 6;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint64_t n;
    char *endptr;
    
    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (buffer[0] == '\0') {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Error: Input too large, result would overflow\n");
        return 1;
    }
    
    if (*endptr != '\0' || endptr == buffer) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    errno = 0;
    uint64_t result = sum_of_squares(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Error: Input too large, result would overflow\n");
        return 1;
    }
    
    printf("Sum of squares: %" PRIu64 "\n", result);
    
    return 0;
}