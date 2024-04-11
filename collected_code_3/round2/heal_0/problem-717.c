#include <math.h>
#include <stdio.h>

double standard_deviation(double* data, int n) {
    double sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i = 0; i < n; ++i) {
        sum += data[i];
    }

    mean = sum/n;

    for(i = 0; i < n; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/n);
}

int main() {
    int n, i;
    double data[100];

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(i = 0; i < n; ++i)
        scanf("%lf", &data[i]);

    printf("Standard Deviation = %.6lf", standard_deviation(data, n));

    return 0;
}