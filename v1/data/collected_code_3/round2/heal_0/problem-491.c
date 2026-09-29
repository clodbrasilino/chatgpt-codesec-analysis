#include <stdio.h>
#include <math.h>

double geometricSum(int a, int r, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a * pow(r, i);
    }
    return sum;
}

int main() {
    int a = 1;
    int r = 2;
    int n = 10;
    double sum = geometricSum(a, r, n);
    printf("The sum of the geometric progression series is: %.2f\n", sum);
    return 0;
}