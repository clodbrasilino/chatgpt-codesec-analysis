#include <stdio.h>
#include <math.h>

double geometric_sum(int n) {
    if (n < 0) {
        return 0.0;
    }
    if (n == 0) {
        return 1.0;
    } else {
        return 1.0 / pow(2, n) + geometric_sum(n - 1);
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:315,execs:313,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Geometric sum of %d is: %lf\n", n, geometric_sum(n));
    return 0;
}