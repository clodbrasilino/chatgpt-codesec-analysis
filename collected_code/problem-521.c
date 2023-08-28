#include<stdio.h>

int isScalene(int a, int b, int c) {
    if (a != b && a != c && b != c) {
        return 1;
    }
    return 0;
}

int main() {
    int side1, side2, side3;
    
    printf("Enter the three sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);
    
    if (isScalene(side1, side2, side3)) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }
    
    return 0;
}