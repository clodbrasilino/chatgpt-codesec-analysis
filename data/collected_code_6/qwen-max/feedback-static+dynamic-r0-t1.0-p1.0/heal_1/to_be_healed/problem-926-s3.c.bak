#include <stdio.h>

long derangement(long n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    long a = 1, b = 0, temp;
    for (long i = 0; i <= n; ++i) {
        temp = (i + 1) * (a + b);
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) return 1;
    if (n < 0) return 1;
    printf("The %ld-th derangement number is: %ld\n", n, derangement(n));
    return 0;
}