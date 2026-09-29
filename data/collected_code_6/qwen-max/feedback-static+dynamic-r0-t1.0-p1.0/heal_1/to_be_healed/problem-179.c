#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_keith_number(long num) {
    long temp = num, digits[50], sum = 0, count = 0;
    while (temp > 0) {
        digits[count++] = temp % 10;
        temp /= 10;
    }
    long k = count;
    for (long i = count; i <= num; i++) {
        for (long j = 1; j < k; j++) {
            sum += digits[j];
        }
        if (sum > num) break;
        if (sum == num && i != count) return true;
        for (long j = k - 1; j > 0; j--) {
            digits[j] = digits[j - 1];
        }
        digits[0] = sum;
        sum = 0;
    }
    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:468,execs:190,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (is_keith_number(number)) {
        printf("%ld is a Keith number.\n", number);
    } else {
        printf("%ld is not a Keith number.\n", number);
    }
    return 0;
}