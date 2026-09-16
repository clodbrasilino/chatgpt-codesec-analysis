#include <stdio.h>

int have_opposite_signs(int x, int y) {
    return (x ^ y) < 0;
}

int main() {
    int a = -5;
    int b = 10;
    if (have_opposite_signs(a, b)) {
        printf("The integers have opposite signs.\n");
    } else {
        printf("The integers do not have opposite signs.\n");
    }
    return 0;
}