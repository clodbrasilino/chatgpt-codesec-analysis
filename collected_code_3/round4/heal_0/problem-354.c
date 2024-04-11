#include <stdio.h>

int nthTerm(int a, int d, int n) {
    return (a + (n - 1) * d);
}

int main() {
    int a, d, n;
    printf("Enter the first term: ");
    scanf("%d", &a);
    printf("Enter the common difference: ");
    scanf("%d", &d);
    printf("Enter the term number: ");
    scanf("%d", &n);
    printf("The %dth term of the arithmetic progression is: %d\n", n, nthTerm(a, d, n));
    return 0;
}