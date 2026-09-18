#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

int64_t maxCuboidVolume(int sum) {
    int64_t max_vol = 0;
    for (int l = 1; l <= sum / 3; l++) {
        for (int b = l; b <= (sum - l) / 2; b++) {
            int h = sum - l - b;
            if (h > 0 && h >= b) {
                int64_t vol = (int64_t)l * (int64_t)b * (int64_t)h;
                if (vol > max_vol) {
                    max_vol = vol;
                }
            }
        }
    }
    return max_vol;
}

int main() {
    int sum;
    printf("Enter the sum of the sides: ");
    if (scanf("%d", &sum) != 1 || sum < 3) {
        printf("Sum must be at least 3\n");
        return 1;
    }
    int64_t max_volume = maxCuboidVolume(sum);
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Maximum volume: %lld\n", max_volume);
    return 0;
}