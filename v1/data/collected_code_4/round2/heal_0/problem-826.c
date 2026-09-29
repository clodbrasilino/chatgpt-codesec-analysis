#include <stdio.h>

enum TriangleType {
    EQUILATERAL,
    ISOSCELES,
    SCALENE,
    NOT_A_TRIANGLE
};

enum TriangleType getTriangleType(int a, int b, int c) {
    if(a <= 0 || b <= 0 || c <= 0 || a+b <= c || a+c <= b || b+c <= a) {
        return NOT_A_TRIANGLE;
    }
    else if(a == b && b == c) {
        return EQUILATERAL;
    }
    else if(a == b || b == c || c == a) {
        return ISOSCELES;
    }
    return SCALENE;
}

int main() {
    int a, b, c;

    printf("Enter sides of the triangle: ");
    scanf("%d %d %d", &a, &b, &c);

    enum TriangleType type = getTriangleType(a, b, c);

    switch(type) {
        case NOT_A_TRIANGLE:
            printf("The sides do not form a triangle.\n"); 
            break;
        case EQUILATERAL:
            printf("Equilateral triangle.\n"); 
            break;
        case ISOSCELES:
            printf("Isosceles triangle.\n"); 
            break;
        case SCALENE:
            printf("Scalene triangle.\n"); 
            break;
        default:
            break;
    }

    return 0;
}