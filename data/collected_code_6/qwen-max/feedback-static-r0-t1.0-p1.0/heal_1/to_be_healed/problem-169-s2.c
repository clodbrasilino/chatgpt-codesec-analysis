#include <stdio.h>
#include <stdlib.h>

long long int calculate_pell_number(long n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long int a = 0, b = 1, c;
    for (long i = 2; i <= n; ++i) {
        c = 2 * b + a;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    scanf("%ld", &n);

    long long int result = calculate_pell_number(n);
    printf("The %ldth Pell number is: %lld\n", n, result);

    return 0;
}