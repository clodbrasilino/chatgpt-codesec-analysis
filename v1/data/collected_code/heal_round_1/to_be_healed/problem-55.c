#include <stdio.h>

double findGeometricTerm(double firstTerm, double commonRatio, int n) {
    double term = firstTerm;

    for (int i = 1; i < n; i++) {
        term *= commonRatio;
    }

    return term;
}

int main() {
    double firstTerm, commonRatio;
    int n;

    printf("Enter the first term: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'firstTerm' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &firstTerm);

    printf("Enter the common ratio: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'commonRatio' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &commonRatio);

    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    /* Possible weaknesses found:
     *  Cannot determine that 'firstTerm' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'commonRatio' is initialized [premium-bughuntingUninit]
     */
    double nthTerm = findGeometricTerm(firstTerm, commonRatio, n);

    printf("The %d-th term of the geometric series is: %.2lf\n", n, nthTerm);

    return 0;
}