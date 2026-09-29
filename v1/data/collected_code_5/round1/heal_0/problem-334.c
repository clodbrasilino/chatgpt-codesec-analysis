#include <stdio.h>
#include <stdbool.h>

bool isValidTriangle(int a, int b, int c) {
    if(a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
}

int main() {
    int sideA, sideB, sideC;
    printf("Enter three sides of triangle: ");
    scanf("%d %d %d", &sideA, &sideB, &sideC);

    if(isValidTriangle(sideA, sideB, sideC)) {
        printf("This is a valid triangle.\n");
    } else {
        printf("This is not a valid triangle.\n");
    }
    return 0;
}