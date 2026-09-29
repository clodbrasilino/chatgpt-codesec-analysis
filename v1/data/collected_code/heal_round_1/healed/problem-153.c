#include <stdio.h>

void findVertex(int a, int b, int c) {
    float x = -b / (2.0 * a);
    float y = a * x * x + b * x + c;
    printf("Vertex: (%f, %f)\n", x, y);
}

int main() {
    int a = 0, b = 0, c = 0;
    printf("Enter coefficients a, b, and c: ");
    scanf("%d %d %d", &a, &b, &c);
    findVertex(a, b, c);
    return 0;
}