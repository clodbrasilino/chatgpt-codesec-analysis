#include <stdio.h>

int maxTriangles(int n) {
    return n * (n - 1) * (n - 2) / 6;
}

int main() {
    int n;
    printf("Enter the number of sides: ");
    scanf("%d", &n);
    printf("Maximum number of equilateral triangles: %d\n", maxTriangles(n));
    return 0;
}