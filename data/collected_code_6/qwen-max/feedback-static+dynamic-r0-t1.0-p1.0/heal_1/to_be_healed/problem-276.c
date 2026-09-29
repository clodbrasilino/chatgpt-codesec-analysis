#include <stdio.h>
#include <math.h>

double calculate_cylinder_volume(double radius, double height) {
    return M_PI * pow(radius, 2) * height;
}

int main() {
    /* Possible weaknesses found:
     *  The scope of the variable 'volume' can be reduced. [variableScope]
     */
    double radius, height, volume;
    if (scanf("%lf %lf", &radius, &height) == 2) {
        volume = calculate_cylinder_volume(radius, height);
        printf("Volume of the cylinder: %.2f\n", volume);
    }
    return 0;
}