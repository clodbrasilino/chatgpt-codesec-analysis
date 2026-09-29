#include <stdio.h>

int compute_lateral_surface_area(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return -1;
    }
    return 2 * height * (length + width);
}

int main() {
    int l = 5;
    int w = 4;
    int h = 3;

    if (l <= 0 || w <= 0 || h <= 0) {
        printf("Invalid dimensions\n");
        return 1;
    }

    int result = compute_lateral_surface_area(l, w, h);
    
    printf("%d\n", result);
    
    return 0;
}