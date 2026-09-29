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
             *  Condition 'k>0' is always true [knownConditionTrueFalse]
             *  Condition 'k>0' is always true
             */
            if (k > 0) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 458976 * 4679 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1004,execs:517,op:havoc,rep:5)
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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:234,execs:141,op:havoc,rep:1; likely memory-safety defect
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