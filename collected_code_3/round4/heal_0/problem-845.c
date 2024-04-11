#include <stdio.h>
#include <math.h>

int findNumberOfDigits(int n) {
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
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Number of digits in %d! is %d", num, findNumberOfDigits(num));
    return 0;
}