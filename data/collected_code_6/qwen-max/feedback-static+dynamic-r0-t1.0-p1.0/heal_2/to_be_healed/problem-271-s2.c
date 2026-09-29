#include <stdio.h>
#include <stdint.h>

unsigned long long sum_of_fifth_powers(int n) {
    unsigned long long sum = 0;
    int i = 1;
    while (n > 0) {
        unsigned long long temp = 2 * i;
        sum += temp * temp * temp * temp * temp;
        i++;
        n--;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:46805,execs:2526,op:havoc,rep:11; likely memory-safety defect
  */

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Enter a positive integer.\n");
        return 1;
    }
    unsigned long long result = sum_of_fifth_powers(n);
    printf("%llu\n", result);
    return 0;
}