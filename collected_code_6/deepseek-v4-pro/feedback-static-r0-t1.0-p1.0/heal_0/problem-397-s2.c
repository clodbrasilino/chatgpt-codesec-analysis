#include <stdio.h>

double median_of_three(int a, int b, int c) {
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return b;
    }
    if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return a;
    }
    return c;
}

int main(void) {
    int x = 10, y = 20, z = 15;

    printf("Median of %d, %d, %d is %.1f\n", x, y, z, median_of_three(x, y, z));

    return 0;
}