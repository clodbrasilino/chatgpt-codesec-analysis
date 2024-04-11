#include <stdio.h>
#include <math.h>

double geometricTerm(int a, int r, int n) {
    return a * pow(r, n - 1);
}

int main() {
    int a = 2, r = 3, n = 4;
    double term = geometricTerm(a, r, n);
    printf("The %d-th term of the geometric series is: %.2f\n", n, term);
    return 0;
}