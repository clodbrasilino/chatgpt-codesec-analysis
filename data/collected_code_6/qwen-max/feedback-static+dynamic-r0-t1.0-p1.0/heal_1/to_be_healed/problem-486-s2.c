#include <stdio.h>
#include <math.h>

double factorial(int n) {
    if (n == 0 || n == 1) return 1.0;
    return n * factorial(n - 1);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0.2255859375, got <no output>
  *  test case 0 failed: expected 0.13656454808718185, got <no output>
  *  test case 2 failed: expected 0.227030335488, got <no output>
  */

double binomial_probability(int n, int k, double p) {
    double q = 1.0 - p;
    double numerator = factorial(n);
    double denominator = factorial(k) * factorial(n - k);
    double result = (numerator / denominator) * pow(p, k) * pow(q, n - k);
    return result;
}

int main() {
    int n = 10;
    int k = 5;
    double p = 0.5;

    double probability = binomial_probability(n, k, p);
    printf("The binomial probability is: %f\n", probability);

    return 0;
}