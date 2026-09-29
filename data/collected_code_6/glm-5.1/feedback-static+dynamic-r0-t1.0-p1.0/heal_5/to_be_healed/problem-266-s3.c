#include <stdio.h>
#include <limits.h>

int lateral_surface_area(int side) {
    if (side < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'side>46340' is not redundant
     */
    if (side > 46340) {
        return -1;
    }
    /* Possible weaknesses found:
     *  Either the condition 'side>46340' is redundant or there is signed integer overflow for expression '4*side*side'. [integerOverflowCond]
     *  Integer overflow
     * UBSan: signed integer overflow: 146664 * 36666 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:3829,execs:1548,op:havoc,rep:1)
     */
    return 4 * side * side;
}

int main() {
    int side;
    if (scanf("%d", &side) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int area = lateral_surface_area(side);
    if (area == -1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("%d\n", area);
    return 0;
}