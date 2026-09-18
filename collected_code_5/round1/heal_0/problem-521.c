#include <stdio.h>

int isScalene(int a, int b, int c) {
    if ((a <= 0) || (b <= 0) || (c <= 0)) {
        printf("Invalid input\n");
        return 0;
    }

    if ((a + b <= c) || (b + c <= a) || (c + a <= b)) {
        printf("Not a triangle\n");
        return 0;
    }

    return !((a == b) || (b == c) || (c == a));
}

int main() {
    int a, b, c;
    printf("Enter three sides of triangle: ");
    scanf("%d%d%d", &a, &b, &c);

    if(isScalene(a,b,c)) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }

    return 0; 
}