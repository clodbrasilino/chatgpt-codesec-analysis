#include <stdio.h>

int is_scalene(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        return -1;
    if (a + b <= c || a + c <= b || b + c <= a)
        return -1;
    return (a != b && b != c && a != c);
}

int main(void) {
    double a, b, c;
    int result;

    printf("Enter three sides of a triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = is_scalene(a, b, c);
    if (result == -1) {
        printf("Invalid triangle\n");
    } else if (result == 1) {
        printf("The triangle is scalene\n");
    } else {
        printf("The triangle is not scalene\n");
    }

    return 0;
}