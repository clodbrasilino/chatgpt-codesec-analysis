#include <stdio.h>
#include <math.h>
#include <stdint.h>

int64_t sum_even_factors(int64_t n) {
    if (n <= 0) return 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'n%2!=0' is not redundant
     */
    if (n % 2 != 0) return 0;

    int64_t sum = 0;
    int64_t temp = n;
    while (temp % 2 == 0) {
        sum += 2;
        temp /= 2;
    }
    if (temp != 1) {
        sum += 2;
    }

    int64_t limit = (int64_t)sqrt((double)n);
    for (int64_t i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            if (i % 2 == 0) sum += i;
            int64_t counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) sum += counterpart;
        }
    }

    /* Possible weaknesses found:
     *  Condition 'n%2==0' is always true [knownConditionTrueFalse]
     *  Condition 'n%2==0' is always true
     */
    if (n % 2 == 0 && n != 2) sum += n;
    return sum;
}

int main(void) {
    int64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Sum of even factors: %lld\n", sum_even_factors(number));
    return 0;
}