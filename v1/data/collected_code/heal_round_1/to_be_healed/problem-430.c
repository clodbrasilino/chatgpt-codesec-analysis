#include <stdio.h>

void findDirectrix(double a, double b, double c) {
    if (a == 0) {
        printf("The directrix is parallel to the y-axis.");
    } else {
        double p = (b * b - 4 * a * c) / (4 * a);
        printf("The directrix is y = %.2lf\n", -p);
    }
}

int main() {
    double a, b, c;
    printf("Enter the coefficients (a, b, c) of the parabola:\n");
    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf %lf %lf", &a, &b, &c);
    /* Possible weaknesses found:
     *  Cannot determine that 'c' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    findDirectrix(a, b, c);
    return 0;
}