#include<stdio.h>
#include<math.h>

int isPrime(int n) {
    if(n <= 1)
        return 0;
    if(n <= 3)
        return 1;
    if(n%2 == 0 || n%3 == 0)
        return 0;
    for(int i=5; i*i<=n; i+=6)
        if(n%i == 0 || n%(i+2) == 0)
            return 0;
    return 1;
}

int sumPrimeDivisors(int n){
    int sum = 0;
    for(int i = 1; i <= sqrt(n); i++) {
        if(n%i == 0) {
            if(i == n/i) {
                if(isPrime(i))
                    sum += i;
            } else {
                if(isPrime(i))
                    sum += i;
                if(isPrime(n/i))
                    sum += n/i;
            }
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    printf("Sum of prime divisors: %d\n", sumPrimeDivisors(n));
    return 0;
}