#include <stdio.h>

double findGeometricTerm(double firstTerm, double commonRatio, int n) {
    double term = firstTerm;

    for (int i = 1; i < n; i++) {
        term *= commonRatio;
    }

    return term;
}

int main() {
    double firstTerm = 0.0, commonRatio = 0.0;
    int n = 0;

    printf("Enter the first term: ");
    scanf("%lf", &firstTerm);

    printf("Enter the common ratio: ");
    scanf("%lf", &commonRatio);

    printf("Enter the value of n: ");
    scanf("%d", &n);

    double nthTerm = findGeometricTerm(firstTerm, commonRatio, n);

    printf("The %d-th term of the geometric series is: %.2lf\n", n, nthTerm);

    return 0;
}