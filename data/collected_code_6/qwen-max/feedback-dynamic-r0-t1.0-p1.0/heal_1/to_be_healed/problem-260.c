#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long num) {
    if (num <= 1) return false;
    if (num % 2 == 0) return num == 2;
    for (long i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

long newman_shanks_williams(long n) {
    long a = 1, b = 1;
    for (long i = 1; ; i++) {
        long c = 4 * a + b;
        a = b;
        b = c;
        if (is_prime(c)) {
            if (i == n) return c;
        }
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:2664,execs:123,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    long result = newman_shanks_williams(n);
    printf("The %dth Newman–Shanks–Williams prime number is: %ld\n", n, result);
    return 0;
}