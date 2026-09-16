#include <stdio.h>

double calculate_lateral_surface_area(double side) {
    return 4.0 * side * side;
}

int main() {
    /* Possible weaknesses found:
     *  The scope of the variable 'area' can be reduced. [variableScope]
     */
    double side, area;
    if (scanf("%lf", &side) == 1) {
        area = calculate_lateral_surface_area(side);
        printf("Lateral Surface Area: %.2lf\n", area);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}