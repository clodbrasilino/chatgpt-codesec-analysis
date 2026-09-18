#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

int64_t maxVolume(int64_t S) {
    int64_t a = S / 3;
    int64_t b = (S - a) / 2;
    int64_t c = S - a - b;
    return a * b * c;
}

int main(void) {
    int64_t sumSides;
    printf("Enter sum of sides: ");
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