#include <stdio.h>
#include <math.h>

int sumOfEvenFactors(int n) {
    int sum = 0;
    int factor = 2;
    for (factor = 2; factor <= sqrt(n); factor++) {
        if (n % factor == 0) {
            if (factor % 2 == 0) {
                sum = sum + factor;
            }
            if ((n / factor) % 2 == 0 && factor != (n / factor)) {
                sum = sum + (n / factor);
            }
        }
    }
    if (n % 2 == 0) {
        sum = sum + n;
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Sum of even factors of %d is %d", num, sumOfEvenFactors(num));
    return 0;
}