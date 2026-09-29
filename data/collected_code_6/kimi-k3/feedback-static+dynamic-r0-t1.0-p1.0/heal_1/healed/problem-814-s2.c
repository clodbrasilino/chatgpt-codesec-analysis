#include <stdio.h>

double rhombus_area(double diagonal1, double diagonal2) {
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    
    if (scanf("%lf %lf", &d1, &d2) != 2) {
        return 1;
    }
    
    area = rhombus_area(d1, d2);
    
    printf("%.0f\n", area);
    
    return 0;
}