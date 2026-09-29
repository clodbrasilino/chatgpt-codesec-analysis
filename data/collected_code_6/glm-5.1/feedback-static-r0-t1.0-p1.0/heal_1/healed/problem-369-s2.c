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
    
    int result = compute_lateral_surface_area(l, w, h);
    
    if (result == -1) {
        printf("Invalid dimensions\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}