#include <stdio.h>
#include <math.h>

#define MAX 1000

int findFirstDigit(int n) {
    double fact = 0;
    for (int i=1; i<=n; i++)
        fact += log10(i);
    return (int)pow(10, fact - floor(fact));
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("First digit in %d! is %d", num, findFirstDigit(num));
    return 0;
}