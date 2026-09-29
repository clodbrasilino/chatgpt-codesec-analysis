#include <stdio.h>
#include <math.h>

int is_valid_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a, b, c;
    a = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    b = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
    c = sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2));

    return a + b > c && b + c > a && a + c > b;
}

int main() {
    double x1, y1, x2, y2, x3, y3;

    printf("Enter the coordinates (x1, y1, x2, y2, x3, y3): ");
    if(scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
        fprintf(stderr, "Input error: Please enter valid numbers.\n");
        return 1;
    }

    if(is_valid_triangle(x1, y1, x2, y2, x3, y3)) {
        printf("The points form a valid triangle.\n");
    } else {
        printf("The points do not form a valid triangle.\n");
    }

    return 0;
}