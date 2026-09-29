#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 2
  *  test case 2 failed: expected 5, got 12
  *  test case 0 failed: expected 11, got 29
  */

long long jacobsthal(long n) {
    if (n <= 1) return n;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long a = 0, b = 1, c;
    for (long i = 2; i <= n; ++i) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    scanf("%ld", &n);
    printf("The %ldth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return 0;
}