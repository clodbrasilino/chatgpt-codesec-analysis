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
    int n = 0, k = 0;
    double p = 0.0;

    printf("Enter the total number of trials (n): ");
    scanf("%d", &n);

    printf("Enter the number of successful trials (k): ");
    scanf("%d", &k);

    printf("Enter the probability of success (p): ");
    scanf("%lf", &p);

    double result = binomialProbability(n, k, p);
    printf("\nBinomial Probability: %.6lf\n", result);

    return 0;
}