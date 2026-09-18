#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int count_primes(int num) {
    int count = 0;
    for (int i = 2; i < num; i++) {
        if (is_prime(i)) count++;
    }
    return count;
}

int main(void) {
    int num;
    printf("Enter a non-negative number: ");
    scanf("%d", &num);
    if (num < 0) {
        printf("The number must be non-negative!\n");
        return -1;
    }
    printf("There are %d prime numbers less than %d.\n", count_primes(num), num);
    return 0;
}