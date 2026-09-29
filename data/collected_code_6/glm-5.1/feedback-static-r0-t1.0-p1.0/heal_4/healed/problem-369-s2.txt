#include <stdio.h>

int compute_lateral_surface_area(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return -1;
    }
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