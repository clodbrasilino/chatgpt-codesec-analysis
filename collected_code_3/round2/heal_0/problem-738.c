#include <stdio.h>
#include <math.h>

double geometricSum(int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += pow(0.5, i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Geometric sum: %f\n", geometricSum(n));
    return 0;
}