#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t maxVolume(int64_t S) {
    if (S < 3) {
        return 0;
    }
    int64_t a = S / 3;
    int64_t b = (S - a) / 2;
    int64_t c = S - a - b;
    if (a < 0 || b < 0 || c < 0) {
        return 0;
    }
    if (b > 0 && a > INT64_MAX / b) {
        return 0;
    }
    int64_t ab = a * b;
    if (c > 0 && ab > INT64_MAX / c) {
        return 0;
    }
    return ab * c;
}

int main(void) {
    int64_t sumSides;
    printf("Enter sum of sides: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &sumSides) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (sumSides < 3) {
        fprintf(stderr, "Sum must be at least 3\n");
        return 1;
    }
    int64_t volume = maxVolume(sumSides);
    printf("Maximum volume: %" PRId64 "\n", volume);
    return 0;
}