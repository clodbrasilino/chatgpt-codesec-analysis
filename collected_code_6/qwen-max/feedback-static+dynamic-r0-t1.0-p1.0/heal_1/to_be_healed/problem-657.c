#include <stdio.h>
#include <math.h>

long long factorial(long num) {
    if (num == 0) return 1;
    long long result = 1;
    for (long i = 1; i <= num; ++i) {
        result *= i;
    }
    return result;
}

int firstDigitOfFactorial(long num) {
    long long fact = factorial(num);
    while (fact >= 10) {
        fact /= 10;
    }
    return (int)fact;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:8,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    long num;
    printf("Enter a number: ");
    scanf("%ld", &num);
    int firstDigit = firstDigitOfFactorial(num);
    printf("The first digit in the factorial of %ld is %d\n", num, firstDigit);
    return 0;
}