#include <stdio.h>
#include <math.h>

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    
    if (scanf("%lf %lf", &d1, &d2) != 2) {
        return 1;
    }
    
    area = rhombus_area(d1, d2);
    
    if (area < 0.0) {
        return 1;
    }
    
    printf("%.2f\n", area);
    
    return 0;
}