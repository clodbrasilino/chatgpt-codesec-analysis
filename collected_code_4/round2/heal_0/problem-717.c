#include <stdio.h>
#include <math.h>

double calculate_std_dev(int data[], int n) {
    double sum = 0.0, mean, standard_deviation = 0.0;

    for (int i = 0; i < n; ++i) {
        sum += data[i];
    }

    mean = sum/n;

    for (int i = 0; i < n; ++i) {
        standard_deviation += pow(data[i] - mean, 2);
    }

    return sqrt(standard_deviation/n);
}

int main() {
    int data[1000];
    int n;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return -1;
    }
    if (n > 1000 || n <= 0) {
        printf("Invalid number of elements\n");
        return -1;
    }
    printf("Enter elements: ");
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &data[i]) != 1) {
            printf("Invalid input\n");
            return -1;
        }
    printf("\nStandard Deviation = %.6lf", calculate_std_dev(data, n));

    return 0;
}