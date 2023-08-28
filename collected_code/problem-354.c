#include <stdio.h>

int nthTerm(int a, int d, int n) {
    return a + (n-1)*d;
}

int main() {
    int firstTerm = 5;
    int commonDiff = 3;
    int n = 7;
    int result = nthTerm(firstTerm, commonDiff, n);
    printf("The %dth term of the arithmetic progression is: %d", n, result);
    return 0;
}