#include <stdio.h>
#include <math.h>

double factorial(int n) {
    double fact = 1;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

double binomial(int n, int k) {
    double binom = factorial(n) / (factorial(k) * factorial(n - k));
    return binom;
}

double binomial_probability(int n, int k, double p) {
    double binom = binomial(n, k);
    double prob = binom * pow(p, k) * pow(1 - p, n - k);
    return prob;
}

int main() {
    int n, k;
    double p;

    printf("Enter the total number of trials: ");
    scanf("%d", &n);

    printf("Enter the total number of successful trials: ");
    scanf("%d", &k);

    printf("Enter the probability of success on a single trial: ");
    scanf("%lf", &p);

    double result = binomial_probability(n, k, p);

    printf("The binomial probability is: %lf\n", result);

    return 0;
}