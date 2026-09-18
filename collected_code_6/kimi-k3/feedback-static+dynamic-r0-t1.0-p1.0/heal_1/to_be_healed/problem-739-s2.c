#include <stdio.h>
#include <math.h>
#include <limits.h>

int smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    
    double lower = pow(10.0, n - 1);
    double discriminant = 1.0 + 8.0 * lower;
    double sqrt_val = sqrt(discriminant);
    long long k = (long long)ceil((sqrt_val - 1.0) / 2.0);
    
    if (k > INT_MAX) {
        return -1;
    }
    
    return (int)k;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:99,execs:60,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    int result = smallest_triangular_index(n);
    
    if (result == -1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}