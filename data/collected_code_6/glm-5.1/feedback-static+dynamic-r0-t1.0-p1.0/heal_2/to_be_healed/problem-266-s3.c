#include <stdio.h>

int lateral_surface_area(int side) {
    if (side < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1357789412 * 734294471 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:336,execs:228,op:havoc,rep:3)
     * UBSan: signed integer overflow: 222220 * 55555 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:199,execs:144,op:havoc,rep:4)
     * UBSan: signed integer overflow: 4 * 734294471 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:336,execs:228,op:havoc,rep:3)
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