#include <stdio.h>

int max_volume_cuboid(int sum) {
    int maxVol = 0;
    for (int i = 1; i <= sum / 3; i++) {
        for (int j = i; j <= (sum - i) / 2; j++) {
            int k = sum - i - j;
            if (k >= j) {
                int vol = i * j * k;
                if (vol > maxVol) {
                    maxVol = vol;
                }
            }
        }
    }
    return maxVol;
}

int main() {
    int sum;
    printf("Enter the sum of the sides: ");
    if (scanf("%d", &sum) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int maxVol = max_volume_cuboid(sum);
    printf("Maximum volume: %d\n", maxVol);
    return 0;
}