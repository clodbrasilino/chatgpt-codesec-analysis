#include <stdio.h>

int compute_lateral_surface_area(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1285418554 * 13 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:521,execs:328,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * 1504774371 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:521,execs:328,op:havoc,rep:2)
     * UBSan: signed integer overflow: 1333333332 * 13 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1265,execs:770,op:havoc,rep:6)
     */
    return 2 * height * (length + width);
}

int main() {
    int l, w, h;
    
    if (scanf("%d %d %d", &l, &w, &h) != 3) {
        return 1;
    }

    int result = compute_lateral_surface_area(l, w, h);
    
    if (result == -1) {
        printf("Invalid dimensions\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}