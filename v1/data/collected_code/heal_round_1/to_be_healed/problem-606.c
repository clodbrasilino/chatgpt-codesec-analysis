#include<stdio.h>

double degreesToRadians(double degrees) {
    /* Possible weaknesses found:
     *  'M_PI' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    double radians = degrees * (M_PI/180);
    return radians;
}

int main() {
    double degrees;
    printf("Enter degrees: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'degrees' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &degrees);
    /* Possible weaknesses found:
     *  Cannot determine that 'degrees' is initialized [premium-bughuntingUninit]
     */
    double radians = degreesToRadians(degrees);
    printf("Radians: %lf", radians);
    return 0;
}