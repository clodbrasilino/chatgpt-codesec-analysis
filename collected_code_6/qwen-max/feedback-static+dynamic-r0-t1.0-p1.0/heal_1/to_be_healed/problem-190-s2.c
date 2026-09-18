#include <stdio.h>
#include <stdlib.h>

int count_integral_coordinates(int x1, int y1, int x2, int y2) {
    int width = abs(x2 - x1) + 1;
    int height = abs(y2 - y1) + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 60192233 * 125803761 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:13,execs:16,op:(null),pos:0)
     * UBSan: signed integer overflow: 1139355592 * 125803761 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:26,execs:19,op:quick,pos:1)
     * UBSan: signed integer overflow: 1139355592 * 1199545584 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:36,execs:21,op:quick,pos:3)
     */
    return width * height;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000001,time:538,execs:146,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int x1, y1, x2, y2;

    printf("Enter the coordinates of the bottom-left corner (x1, y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter the coordinates of the top-right corner (x2, y2): ");
    scanf("%d %d", &x2, &y2);

    int count = count_integral_coordinates(x1, y1, x2, y2);
    printf("Number of integral coordinates: %d\n", count);

    return 0;
}