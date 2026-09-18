#include <stdio.h>
#include <math.h>

double geometric_sum(int a, int r, int n) {
    double sum = 0;

    if(n < 1 || r == 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return -1;
    }

    for(int i = 0; i < n; i++) {
        sum += a * pow(r, i);
    }

    return sum;
}

int main() {
    int a = 1;
    int r = 2;
    int n = 10;

    double result = geometric_sum(a, r, n);

    if(result != -1) {
        printf("The sum of the geometric progression is: %.2f\n", result);
    }

    return 0;
}