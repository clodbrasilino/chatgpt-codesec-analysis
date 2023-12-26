#include <stdio.h>

void findVertex(int a, int b, int c) {
    float x = -b / (2 * a);
    float y = a * x * x + b * x + c;
    printf("Vertex: (%f, %f)\n", x, y);
}

int main() {
    int a, b, c;
    printf("Enter coefficients a, b, and c: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d %d", &a, &b, &c);
    findVertex(a, b, c);
    return 0;
}