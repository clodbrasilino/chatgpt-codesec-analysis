#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 48, got 72
  *  test case 0 failed: expected 26, got 216
  */

long long sumOfEvenFactors(long long n) {
    if (n % 2 != 0) return 0;

    long long res = 1;
    while (n % 2 == 0) {
        n /= 2;
        res *= 2;
    }

    for (long long f = 3; f <= sqrt(n); f += 2) {
        if (n % f == 0) {
            long long count = 0, curr_term = 1;
            do {
                count++;
                n /= f;
                curr_term *= f;
                if (count > 0 && (curr_term * 2) % 2 == 0) res *= (curr_term * 2);
            } while (n % f == 0);
        }
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 27620352027620352 * 333668 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:639,execs:625,op:havoc,rep:2)
     */
    if (n >= 2) res *= (n + 1);
    return res;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000003,time:811,execs:788,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Sum of even factors: %lld\n", sumOfEvenFactors(n));
    return 0;
}