#include <stdio.h>
#include <stdlib.h>

int countEquilateralTriangles(int n) {
    if (n < 3) return 0;
    int count = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'size<=n' is not redundant
     */
    for (int size = 1; size <= n; ++size) {
        /* Possible weaknesses found:
         *  Assignment 'layers=n-size+1', assigned value is greater than 0
         */
        int layers = n - size + 1;
        /* Possible weaknesses found:
         *  Condition 'layers>0' is always true [knownConditionTrueFalse]
         *  Condition 'layers>0' is always true
         */
        if (layers > 0) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2095702761 + 123076836 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:1571,execs:652,op:havoc,rep:3)
             */
            count += layers * layers;
        }
    }
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000003,time:1781,execs:734,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the size of the equilateral triangle: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    int result = countEquilateralTriangles(n);
    printf("Maximum number of equilateral triangles: %d\n", result);
    return 0;
}