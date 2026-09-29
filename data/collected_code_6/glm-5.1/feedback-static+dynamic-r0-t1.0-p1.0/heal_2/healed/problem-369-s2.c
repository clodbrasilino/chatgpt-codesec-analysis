#include <stdio.h>
#include <stdlib.h>

long long compute_lateral_surface_area(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return -1;
    }
    return 2LL * height * ((long long)length + width);
}

int main() {
    int l, w, h;
    
    if (scanf("%d %d %d", &l, &w, &h) != 3) {
        return 1;
    }

    long long result = compute_lateral_surface_area(l, w, h);
    
    if (result == -1) {
        printf("Invalid dimensions\n");
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}