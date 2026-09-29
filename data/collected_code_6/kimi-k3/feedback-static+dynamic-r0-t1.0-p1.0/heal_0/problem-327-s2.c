#include <stdio.h>
#include <stdbool.h>

bool is_isosceles(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return false;
    }
    return (a == b) || (b == c) || (a == c);
}

int main(void)
{
    double side_a;
    double side_b;
    double side_c;
    int scan_result;

    printf("Enter three side lengths: ");
    scan_result = scanf("%lf %lf %lf", &side_a, &side_b, &side_c);

    if (scan_result != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (is_isosceles(side_a, side_b, side_c)) {
        printf("The triangle is isosceles\n");
    } else {
        printf("The triangle is not isosceles\n");
    }

    return 0;
}