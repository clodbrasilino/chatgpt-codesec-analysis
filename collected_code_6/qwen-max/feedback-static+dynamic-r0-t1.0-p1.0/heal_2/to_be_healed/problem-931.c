#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_valid_input(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

long long sum_of_cubes(long long n) {
    long long result = (n * (n + 1) / 2) * (n * (n + 1) / 2);
    return result;
}

int main() {
    char input[20];
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL || !is_valid_input(input)) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'strtol' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'strtol'
     *  call to undeclared library function 'strtol' with type 'long (const char *, char **, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int n = strtol(input, NULL, 10);
    if (n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the cubes of the first %d natural numbers is: %lld\n", n, result);
    return 0;
}