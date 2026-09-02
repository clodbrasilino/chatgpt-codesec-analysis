#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int sum_of_prime_divisors(int n) {
    if (n <= 1) return 0;
    
    int sum = 0;
    int temp = n;
    
    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0 && is_prime(i)) {
            sum += i;
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    
    if (temp > 1 && is_prime(temp)) {
        sum += temp;
    }
    
    return sum;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long num = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || num <= 0 || num > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    int result = sum_of_prime_divisors((int)num);
    printf("Sum of prime divisors of %ld is: %d\n", num, result);
    
    return EXIT_SUCCESS;
}