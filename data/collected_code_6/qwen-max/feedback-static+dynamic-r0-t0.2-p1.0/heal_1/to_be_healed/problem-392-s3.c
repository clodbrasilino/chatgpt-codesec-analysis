#include <stdio.h>
#include <stdlib.h>

int f(int n) {
    if (n < 12) return n;
    int a = f(n / 2);
    int b = f(n / 3);
    int c = f(n / 4);
    int d = f(n / 5);
    return (a + b + c + d > n) ? (a + b + c + d) : n;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:10694,execs:196,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = f(n);
    printf("Maximum sum: %d\n", result);
    return 0;
}