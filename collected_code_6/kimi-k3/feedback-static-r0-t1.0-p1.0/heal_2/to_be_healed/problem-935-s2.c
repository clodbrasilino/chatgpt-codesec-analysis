#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <inttypes.h>

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
    uint64_t n;
    int scan_result;
    
    printf("Enter a positive integer: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    scan_result = scanf("%" SCNu64, &n);
    
    if (scan_result != 1) {
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