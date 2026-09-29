#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 48, got 72
  *  test case 0 failed: expected 26, got 216
  */

uint64_t sumOfEvenFactors(uint64_t n) {
    if (n % 2 != 0) return 0;

    uint64_t res = 1;
    while (n % 2 == 0) {
        n /= 2;
        res *= 2;
    }

    for (uint64_t f = 3; f <= sqrt(n); f += 2) {
        if (n % f == 0) {
            uint64_t count = 0, curr_term = 1;
            do {
                count++;
                n /= f;
                curr_term *= f;
                if (count > 0 && (curr_term * 2) % 2 == 0) {
                    uint64_t temp = res * (curr_term * 2);
                    if (temp / (curr_term * 2) == res) {
                        res = temp;
                    } else {
                        return 0; // Avoid overflow
                    }
                }
            } while (n % f == 0);
        }
    }

    if (n >= 2) {
        uint64_t temp = res * (n + 1);
        if (temp / (n + 1) == res) {
            res = temp;
        } else {
            return 0; // Avoid overflow
        }
    }
    return res;
}

int main() {
    uint64_t n;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Sum of even factors: %llu\n", sumOfEvenFactors(n));
    return 0;
}