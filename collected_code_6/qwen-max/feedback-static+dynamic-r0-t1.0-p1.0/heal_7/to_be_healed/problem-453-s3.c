#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8, got 11
  *  test case 0 failed: expected 26, got 29
  *  test case 1 failed: expected 48, got 47
  */

long sum_of_even_factors(long n) {
    long sum = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'n%2!=0' is not redundant
     */
    if (n % 2 != 0) return 0;
    for (long i = 2; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    /* Possible weaknesses found:
     *  Condition 'n%2==0' is always true
     *  Condition 'n%2==0' is always true [knownConditionTrueFalse]
     */
    return sum + (n > 1 && n % 2 == 0 ? n : 0);
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long result = sum_of_even_factors(number);
    printf("Sum of even factors is: %ld\n", result);
    return 0;
}