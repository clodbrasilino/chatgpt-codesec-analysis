#include <stdio.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 10, got <no output>
  *  test case 1 failed: expected 18, got <no output>
  */

long sum_of_evens(long l, long r) {
    long sum = 0;
    if (l % 2 != 0) l++;
    for (long i = l; i <= r; i += 2) {
        sum += i;
    }
    return sum;
}

int main() {
    int64_t l, r;
    printf("Enter the range (l r): ");
    if (scanf("%ld %ld", &l, &r) != 2 || l > r) {
        printf("Invalid input or range. Please ensure l is less than or equal to r.\n");
        return 1;
    }
    int64_t result = sum_of_evens(l, r);
    printf("Sum of even numbers between %ld and %ld: %ld\n", l, r, result);
    return 0;
}