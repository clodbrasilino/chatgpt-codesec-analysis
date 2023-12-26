#include <stdio.h>

double binomialProbability(int n, int k, double p) {
    double q = 1 - p;
    double coefficient = 1;
    double probability = 1;

    for (int i = 1; i <= k; i++) {
        coefficient *= (n - i + 1);
        coefficient /= i;
        probability *= p;
    }

    probability *= q;

    return coefficient * probability;
}

int main() {
    int n, k;
    double p;

    printf("Enter the total number of trials (n): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    printf("Enter the number of successful trials (k): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'k' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &k);

    printf("Enter the probability of success (p): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'p' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &p);

    /* Possible weaknesses found:
     *  Cannot determine that 'p' is initialized [premium-bughuntingUninit]
     */
    double result = binomialProbability(n, k, p);

    printf("\nBinomial Probability: %.6lf\n", result);

    return 0;
}