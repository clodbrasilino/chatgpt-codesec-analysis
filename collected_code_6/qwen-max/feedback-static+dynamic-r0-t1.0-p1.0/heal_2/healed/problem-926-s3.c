#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_input_valid(long n) {
    return n >= 0 && n < 14; // Restrict input to prevent overflow
}

long derangement(long n) {
    long a = 1, b = 0;
    for (long i = 0; i <= n; ++i) {
        long temp = (i + 1) * (a + b);
        if ((i + 1) > 0 && (a + b) > 0 && (temp / (i + 1)) != (a + b)) return -1;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || !is_input_valid(n)) return 1;
    long result = derangement(n);
    if (result == -1) {
        printf("Error: Integer overflow detected.\n");
    } else {
        printf("The %ld-th derangement number is: %ld\n", n, result);
    }
    return 0;
}