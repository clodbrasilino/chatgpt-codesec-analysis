#include <stdio.h>
#include <math.h>
#include <limits.h>

int maxCuboidVolume(int sum) {
    int max_vol = 0;
    for (int l = 1; l <= sum / 3; l++) {
        for (int b = l; b <= (sum - l) / 2; b++) {
            int h = sum - l - b;
            if (h > 0 && h >= b) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 358337 * 5993 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:1155,execs:536,op:havoc,rep:5)
                 */
                int vol = l * b * h;
                if (vol > max_vol) {
                    max_vol = vol;
                }
            }
        }
    }
    return max_vol;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:645,execs:310,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int sum;
    printf("Enter the sum of the sides: ");
    if (scanf("%d", &sum) != 1 || sum < 3) {
        printf("Sum must be at least 3\n");
        return 1;
    }
    int max_volume = maxCuboidVolume(sum);
    printf("Maximum volume: %d\n", max_volume);
    return 0;
}