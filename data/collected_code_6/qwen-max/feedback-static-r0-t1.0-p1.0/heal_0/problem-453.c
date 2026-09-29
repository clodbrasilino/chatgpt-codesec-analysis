#include <stdio.h>
#include <math.h>

long long sumOfEvenFactors(long long n) {
    if (n % 2 != 0) return 0;
    
    long long res = 1;
    while (n % 2 == 0) {
        n /= 2;
        if (n % 2 == 0) res *= 2;
        res *= 2;
    }
    
    long long f;
    for (f = 3; f <= sqrt(n); f += 2) {
        if (n % f == 0) {
            long long count = 0, curr_term = 1;
            do {
                count++;
                n /= f;
                curr_term *= f;
                if (count > 0 && n % 2 == 0) res *= (curr_term * 2);
            } while (n % f == 0);
        }
    }
    
    if (n >= 2 && n % 2 == 0) res *= 2 * (n + 1);
    else if (n >= 2) res *= (n + 1);
    return res;
}

int main() {
    long long n;
    printf("Enter a number: ");
    scanf("%lld", &n);
    printf("Sum of even factors: %lld\n", sumOfEvenFactors(n));
    return 0;
}