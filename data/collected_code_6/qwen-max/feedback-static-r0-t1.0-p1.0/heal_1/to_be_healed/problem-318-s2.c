#include <stdio.h>

int max_volume_cuboid(int sum) {
    int maxVol = 0;
    for (int i = 1; i < sum; i++) {
        /* Possible weaknesses found:
         *  Assuming that condition 'j<sum-i' is not redundant
         */
        for (int j = 1; j < sum - i; j++) {
            /* Possible weaknesses found:
             *  Assignment 'k=sum-i-j', assigned value is greater than 0
             */
            int k = sum - i - j;
            /* Possible weaknesses found:
             *  Condition 'k>0' is always true
             *  Condition 'k>0' is always true [knownConditionTrueFalse]
             */
            if (k > 0) {
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