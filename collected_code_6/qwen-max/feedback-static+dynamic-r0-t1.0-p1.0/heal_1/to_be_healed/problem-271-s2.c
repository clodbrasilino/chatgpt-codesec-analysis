#include <stdio.h>

unsigned long long sum_of_fifth_powers(int n) {
    unsigned long long sum = 0;
    int i = 1;
    while (n > 0) {
        sum += (2 * i) * (2 * i) * (2 * i) * (2 * i) * (2 * i);
        i++;
        n--;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:8,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("Enter a positive integer.\n");
        return 1;
    }
    unsigned long long result = sum_of_fifth_powers(n);
    printf("%llu\n", result);
    return 0;
}