#include <stdio.h>
#include <math.h>

int countDigitsInFactorial(int n) {
    if (n < 0)
        return 0;
    if (n <= 1)
        return 1;
    double x = ((n * log10(n / M_E) + log10(2 * M_PI * n) / 2.0));
    return floor(x) + 1;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Number of digits in %d! is %d", num, countDigitsInFactorial(num));
    return 0;
}