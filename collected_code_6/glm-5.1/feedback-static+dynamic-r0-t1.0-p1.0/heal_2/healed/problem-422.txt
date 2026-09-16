#include <stdio.h>

long double find_average_of_cubes(unsigned int n) {
    if (n == 0) {
        return 0.0L;
    }
    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    sum *= sum;
    return (long double)sum / n;
}

int main(void) {
    unsigned int n;
    if (scanf("%u", &n) != 1) {
        return 1;
    }
    long double avg = find_average_of_cubes(n);
    printf("%.1Lf\n", avg);
    return 0;
}