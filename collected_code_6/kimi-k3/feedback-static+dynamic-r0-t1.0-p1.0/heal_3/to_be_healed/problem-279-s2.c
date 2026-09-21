#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

uint64_t decagonal_number(uint64_t n) {
    return 4 * n * n - 3 * n;
}

int main(void) {
    uint64_t n;
    int result;
    char extra;

    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    result = scanf("%" SCNu64, &n);

    if (result != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    if (scanf("%c", &extra) != EOF && extra != '\n') {
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