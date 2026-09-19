#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool is_valid_input(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

long long sum_of_cubes(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1486312458620913336 * 1486312458620913336 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:33,execs:44,op:havoc,rep:2)
     */
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
    int n = (int)strtol(input, NULL, 10);
    if (n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the cubes of the first %d natural numbers is: %lld\n", n, result);
    return 0;
}