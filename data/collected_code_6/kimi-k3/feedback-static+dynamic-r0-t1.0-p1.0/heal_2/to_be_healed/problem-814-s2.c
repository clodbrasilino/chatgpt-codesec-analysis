#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 25, got <no output>
  *  test case 0 failed: expected 100, got <no output>
  *  test case 2 failed: expected 4, got <no output>
  */

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