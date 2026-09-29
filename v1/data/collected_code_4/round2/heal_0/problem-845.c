#include <stdio.h>
#include <math.h>

double findDigits(int n) {
    if (n < 0)
        return 0;
    if (n <= 1)
        return 1;
    double digits = 0;
    for (int i=2; i<=n; i++)
        digits += log10(i);
    return floor(digits) + 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Number of digits in factorial of %d is %0.lf\n", n, findDigits(n));
    return 0;
}