#include <stdio.h>

void findVertex(float a, float b, float c, float *vertexX, float *vertexY) {
    *vertexX = -b / (2 * a);
    *vertexY = c - (b * b) / (4 * a);
}

int main() {
    float a = 1.0;
    float b = -3.0;
    float c = 2.0;

    float vertexX, vertexY;
    findVertex(a, b, c, &vertexX, &vertexY);

    printf("Vertex X: %.2f, Vertex Y: %.2f\n", vertexX, vertexY);

    return 0;
}