#include <stdio.h>
#include <math.h>

long long sumOfEvenFactors(long long n) {
    if (n % 2 != 0) return 0;

    long long res = 0;
    while (n % 2 == 0) {
        res += 2;
        n /= 2;
    }

    for (long long f = 3; f <= sqrt(n); f += 2) {
        if (n % f == 0) {
            long long count = 0, curr_term = 1;
            do {
                count++;
                n /= f;
                curr_term *= f;
            } while (n % f == 0);
            if (count > 0 && (curr_term * 2) % 2 == 0) {
                res += curr_term + 1;
            }
        }
    }

    if (n >= 2) {
        res += n + 1;
    }

    return res - 1;
}

int main() {
    long long n;
    printf("Enter a number: ");
    scanf("%lld", &n);
    long long result = sumOfEvenFactors(n);
    if (result == 0) {
        printf("No even factors\n");
    } else {
        printf("Sum of even factors: %lld\n", result);
    }
    return 0;
}