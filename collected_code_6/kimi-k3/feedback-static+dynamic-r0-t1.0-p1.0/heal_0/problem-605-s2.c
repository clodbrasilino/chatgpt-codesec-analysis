#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int num;
    int status;
    
    printf("Enter an integer: ");
    status = scanf("%d", &num);
    
    if (status != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    if (is_prime(num)) {
        printf("%d is a prime number\n", num);
    } else {
        printf("%d is not a prime number\n", num);
    }
    
    return 0;
}