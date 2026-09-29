#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

int64_t octagonal_number(int64_t n) {
    if (n < 0 || n > 3037000499LL) {
        return -1;
    }
    return n * (3 * n - 2);
}

int main(void) {
    int64_t n;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    
    int64_t result = octagonal_number(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    return 0;
}