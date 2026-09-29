#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int get_min_prime_factor(int n) {
    if (n % 2 == 0) return 2;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return i;
    }
    return n;
}

int count_prime_factors_in_factorial(int n, int p) {
    int count = 0;
    int power = p;
    while (power <= n) {
        count += n / power;
        if (power > n / p) break;
        power *= p;
    }
    return count;
}

bool factorial_divides(int a, int b) {
    if (a > b) return false;
    if (a == b) return true;
    if (a == 0 || a == 1) return true;
    
    int temp_a = a;
    int temp_b = b;
    
    int current_a = a;
    while (current_a > 1) {
        int prime = get_min_prime_factor(current_a);
        int count_in_a = 0;
        while (current_a % prime == 0) {
            count_in_a++;
            current_a /= prime;
        }
        int count_in_b = count_prime_factors_in_factorial(b, prime);
        if (count_in_b < count_in_a) return false;
    }
    
    return true;
}

int last_digit_factorial_division(int a, int b) {
    if (a < 0 || b < 0) return -1;
    if (!factorial_divides(a, b)) return -1;
    if (b == 0 || b == 1) return 1;
    if (a == b) return 1;
    if (a == 0 || a == 1) return 1;
    
    long long result = 1;
    for (int i = a + 1; i <= b; i++) {
        result = (result * (i % 10)) % 10;
        if (result == 0) break;
    }
    
    return (int)result;
}

int main(void) {
    int a, b;
    
    printf("Enter a and b (factorial(a) divides factorial(b)): ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = last_digit_factorial_division(a, b);
    if (result == -1) {
        printf("factorial(%d) does not divide factorial(%d)\n", a, b);
    } else {
        printf("Last digit of factorial(%d)/factorial(%d) is: %d\n", b, a, result);
    }
    
    return EXIT_SUCCESS;
}