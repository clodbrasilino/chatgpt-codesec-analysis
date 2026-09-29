#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 8, got <no output>
  *  test case 0 failed: expected 5, got <no output>
  *  test case 2 failed: expected 7, got <no output>
  */

int count_digits(long num) {
    int count = 0;
    if (num == 0) return 1;
    if (num < 0) num = -num;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000008,time:7065,execs:3407,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    printf("Number of digits: %d\n", count_digits(number));
    return 0;
}