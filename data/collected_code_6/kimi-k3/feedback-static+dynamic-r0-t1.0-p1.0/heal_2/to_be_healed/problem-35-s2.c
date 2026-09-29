#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t rectangular_number(uint32_t n) {
    return (uint64_t)n * ((uint64_t)n + 1);
}

int main(void) {
    uint32_t n;
    int result;

    printf("Enter n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    result = scanf("%" SCNu32, &n);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%" PRIu64 "\n", rectangular_number(n));

    return 0;
}