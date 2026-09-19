#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_keith_number(long n) {
    long t = n;
    int digits[100], k, j, sum = 0;
    for (k = 0; t > 0 && k < 100; ++k) {
        digits[k] = t % 10;
        t /= 10;
    }
    while (sum < n) {
        sum = 0;
        for (j = 0; j < k; ++j) {
            sum += digits[j];
        }
        if (sum == n) return true;
        for (j = 0; j < k - 1; ++j) {
            digits[j] = digits[j + 1];
        }
        digits[k - 1] = sum;
    }
    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:464,execs:482,op:havoc,rep:15; likely memory-safety defect
  */

int main() {
    long number;

    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_keith_number(number)) {
        printf("%ld is a Keith number.\n", number);
    } else {
        printf("%ld is not a Keith number.\n", number);
    }

    return EXIT_SUCCESS;
}