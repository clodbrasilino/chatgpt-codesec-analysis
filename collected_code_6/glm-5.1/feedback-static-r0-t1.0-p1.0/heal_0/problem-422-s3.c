#include <stdio.h>

unsigned long long calculate_cubes_sum(int n) {
    return (unsigned long long)n * (n + 1) / 2 * n * (n + 1) / 2;
}

double find_average_of_cubes(int n) {
    if (n <= 0) {
        return 0.0;
    }
    unsigned long long sum = calculate_cubes_sum(n);
    return (double)sum / (double)n;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    double average = find_average_of_cubes(n);
    printf("%lf\n", average);
    return 0;
}