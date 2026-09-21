#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t compute_difference(int64_t n) {
    if (n < 0) {
        return -1;
    }
    int64_t sum = n * (n + 1) / 2;
    int64_t sum_of_cubes = sum * sum;
    return sum_of_cubes - sum;
}

int main(void) {
    int64_t n;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    printf("%" PRId64 "\n", compute_difference(n));
    return 0;
}