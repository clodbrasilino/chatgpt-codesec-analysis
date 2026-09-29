#include <stdio.h>
#include <math.h>

double calculate_surface_area(double radius, char surface) {
    if (surface == 't' || surface == 'b') {
        return M_PI * pow(radius, 2);
    }
    return 0.0;
}

int main() {
    double radius = 5.0;
    /* Possible weaknesses found:
     *  'surface' is assigned value ''t'' here.
     */
    char surface = 't';
    double area = calculate_surface_area(radius, surface);
    /* Possible weaknesses found:
     *  The comparison 'surface == 't'' is always true because 'surface' and ''t'' represent the same value. [knownConditionTrueFalse]
     *  The comparison 'surface == 't'' is always true because 'surface' and ''t'' represent the same value.
     */
    printf("The %s surface area of the cylinder is: %.2f\n", (surface == 't' ? "top" : "bottom"), area);
    return 0;
}