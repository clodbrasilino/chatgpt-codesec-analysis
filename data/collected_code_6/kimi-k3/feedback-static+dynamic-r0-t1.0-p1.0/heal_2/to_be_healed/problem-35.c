#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

int64_t rectangular_number(uint64_t n, int *err)
{
    if (n == 0 || n > UINT32_MAX) {
        *err = ERANGE;
        return 0;
    }
    
    *err = 0;
    return (int64_t)(n * (n + 1));
}

int main(void)
{
    uint64_t n;
    int err;
    int64_t result;
    
    printf("Enter n: ");
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = rectangular_number(n, &err);
    
    if (err != 0) {
        fprintf(stderr, "Error: n out of valid range\n");
        return EXIT_FAILURE;
    }
    
    printf("Rectangular number: %" PRId64 "\n", result);
    
    return EXIT_SUCCESS;
}