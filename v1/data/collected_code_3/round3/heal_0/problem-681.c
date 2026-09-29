#include <stdio.h>
#include <math.h>

int smallestPrime(int n) {
    if (n <= 1)
        return -1;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return i;
    }
    return n;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int smallest_prime = smallestPrime(num);
    if (smallest_prime == -1)
        printf("No prime divisors as the number is less than or equal to 1.\n");
    else
        printf("Smallest prime divisor is: %d\n", smallest_prime);
    return 0;
}