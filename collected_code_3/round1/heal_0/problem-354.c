#include <stdio.h>

int nthTerm(int a, int d, int n) {
    return (a + (n - 1) * d);
}

int main() {
    int a, d, n;
    printf("Enter the first term, common difference and the term number:\n");
    scanf("%d %d %d", &a, &d, &n);
    printf("The %d-th term of the arithmetic progression is: %d\n", n, nthTerm(a, d, n));
    return 0;
}