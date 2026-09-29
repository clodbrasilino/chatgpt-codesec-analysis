#include <stdio.h>

double rombus_area(double d1, double d2) {
    if(d1 <= 0 || d2 <= 0) {
        printf("Invalid parameters, dimensions must be greater than 0.\n");
        return -1;
    }
    return (d1 * d2) / 2;
}

int main() {
    double d1, d2, area;

    printf("Enter first diagonal: ");
    scanf("%lf", &d1);

    printf("Enter second diagonal: ");
    scanf("%lf", &d2);

    area = rombus_area(d1, d2);

    if(area != -1)
        printf("Area of the rombus: %.2lf\n", area);

    return 0;
}