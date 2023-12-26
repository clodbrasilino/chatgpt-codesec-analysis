#include <stdio.h>

int isPrime(int number) {
    if(number <= 1) return 0;
    for(int i = 2; i <= number/2; i++) {
        if(number % i == 0) {
            return 0;
        }
    }
    return 1;
}

int sumPrimeDivisors(int number) {
    int sum = 0;
    for(int i = 2; i <= number; i++) {
        if(number % i == 0 && isPrime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);
    printf("Sum of all prime divisors: %d\n", sumPrimeDivisors(number));
    return 0;
}