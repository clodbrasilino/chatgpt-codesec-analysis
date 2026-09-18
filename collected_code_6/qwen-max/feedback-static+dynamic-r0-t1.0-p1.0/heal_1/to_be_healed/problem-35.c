#include <stdio.h>

int nthRectangularNumber(int n) {
    return n * (n + 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:677,execs:326,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter n: ");
    if(scanf("%d", &n) == 1) {
        int result = nthRectangularNumber(n);
        printf("The %d-th rectangular number is: %d\n", n, result);
    } else {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
    }
    return 0;
}