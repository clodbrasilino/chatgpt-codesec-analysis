#include <stdio.h>

double harmonicSum(int n) {
    double sum = 0.0;
    for(int i = 1; i <= n; i++) {
        sum += 1.0/i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Harmonic Sum: %.6f\n", harmonicSum(n-1));
    return 0;
}