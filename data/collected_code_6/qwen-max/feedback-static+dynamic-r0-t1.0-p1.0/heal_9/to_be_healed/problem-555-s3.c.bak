#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_of_cubes(long n) {
    if (n > 0x1FFFFF || n < -0x1FFFFF) return 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'n>0' is not redundant
     */
    if (n > 0 && LLONG_MAX / n < n * (n + 1)) return 0;
    if (n < 0 && LLONG_MIN / n > n * (n + 1)) return 0;
    /* Possible weaknesses found:
     *  temp is assigned '(n*(n+1))/2' here.
     */
    int64_t temp = (n * (n + 1)) / 2;
    int64_t temp_sq = temp * temp;
    /* Possible weaknesses found:
     *  Either the condition 'n>0' is redundant or there is division by zero at line 12. [zerodivcond]
     *  Division by zero
     */
    if (temp_sq / temp != temp) return 0;
    return temp_sq;
}

long long sum_of_numbers(long n) {
    if (n > 0x1FFFFF || n < -0x1FFFFF) return 0;
    if (n > 0 && LLONG_MAX / n < 2) return 0;
    if (n < 0 && LLONG_MIN / n > 2) return 0;
    int64_t temp = n * (n + 1);
    return temp / 2;
}

long long difference(long n) {
    return sum_of_cubes(n) - sum_of_numbers(n);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:1130,execs:488,op:quick,pos:6; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}