#include <stdio.h>
#include <limits.h>

int lateral_surface_area(int side) {
    if (side < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 * 1260588259 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:549,execs:340,op:havoc,rep:2)
     */
    if (side > 0 && side > INT_MAX / (4 * side)) {
        return -1;
    }
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