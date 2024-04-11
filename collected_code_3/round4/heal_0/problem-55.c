#include <stdio.h>
#include <math.h>

double nthTermOfGeometricSeries(double firstTerm, double ratio, int nthTerm) {
    return firstTerm * pow(ratio, nthTerm - 1);
}

int main() {
    double firstTerm, ratio;
    int nthTerm;

    printf("Enter the first term of the series: ");
    scanf("%lf", &firstTerm);

    printf("Enter the common ratio: ");
    scanf("%lf", &ratio);

    printf("Enter the term number to find: ");
    scanf("%d", &nthTerm);

    printf("The %dth term of the geometric series is: %.2lf\n", nthTerm, nthTermOfGeometricSeries(firstTerm, ratio, nthTerm));

    return 0;
}