#include <stdio.h>

int countEquilateralTriangles(int n) {
    if (n < 3) return 0;
    int count = 0;
    for (int size = 1; size <= n; ++size) {
        int layers = n - size + 1;
        count += layers * layers;
    }
    return count;
}

int main() {
    int n;
    printf("Enter the size of the equilateral triangle: ");
    scanf("%d", &n);
    int result = countEquilateralTriangles(n);
    printf("Maximum number of equilateral triangles: %d\n", result);
    return 0;
}