#include <stdio.h>

int max_volume_cuboid(int sum) {
    int maxVol = 0;
    for (int i = 1; i < sum - 1; i++) {
        for (int j = 1; j < sum - i - 1; j++) {
            int k = sum - i - j;
            int vol = i * j * k;
            if (vol > maxVol) {
                maxVol = vol;
            }
        }
    }
    return maxVol;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:481,execs:220,op:havoc,rep:6; likely memory-safety defect
  */

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