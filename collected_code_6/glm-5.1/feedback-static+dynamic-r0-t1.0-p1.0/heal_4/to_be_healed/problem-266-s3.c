#include <stdio.h>
#include <limits.h>

int lateral_surface_area(int side) {
    if (side < 0) {
        return -1;
    }
    if (side > INT_MAX / 4) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 266664 * 66666 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:237,execs:120,op:havoc,rep:7)
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