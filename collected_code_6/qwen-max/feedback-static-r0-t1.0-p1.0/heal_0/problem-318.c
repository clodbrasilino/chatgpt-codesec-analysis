#include <stdio.h>

int maxVolumeOfCuboid(int sum) {
    int a, b, c;
    int max_volume = 0;
    for (a = 1; a <= sum / 3; ++a) {
        for (b = a; b <= (sum - a) / 2; ++b) {
            c = sum - a - b;
            int volume = a * b * c;
            if (volume > max_volume) {
                max_volume = volume;
            }
        }
    }
    return max_volume;
}

int main() {
    int sum = 12;
    int max_volume = maxVolumeOfCuboid(sum);
    printf("Maximum volume of the cuboid: %d\n", max_volume);
    return 0;
}