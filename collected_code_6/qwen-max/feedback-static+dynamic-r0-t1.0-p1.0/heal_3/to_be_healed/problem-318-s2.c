#include <stdio.h>
#include <limits.h>

int max_volume_cuboid(int sum) {
    int maxVol = 0;
    if (sum <= 0 || sum > INT_MAX / 3) return 0;
    for (int i = 1; i < sum - 1; i++) {
        for (int j = 1; j < sum - i - 1; j++) {
            int k = sum - i - j;
            if (k > 0) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1090108 * 1970 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:775,execs:374,op:havoc,rep:7)
                 */
                int vol = i * j * k;
                if (vol > maxVol) {
                    maxVol = vol;
                }
            }
        }
    }
    return maxVol;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:324,execs:166,op:havoc,rep:2; likely memory-safety defect
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