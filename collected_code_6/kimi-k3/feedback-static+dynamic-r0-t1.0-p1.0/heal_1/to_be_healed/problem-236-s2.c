#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_equilateral_triangles(long long n) {
    if (n <= 0) {
        return 0;
    }
    
    if (n > 3037000499LL) {
        return -1;
    }
    
    long long total = (n * (n + 2) * (2 * n + 1)) / 8;
    
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:750,execs:361,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    long long n;
    
    if (printf("Enter the number of divisions (n): ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_equilateral_triangles(n);
    
    if (result == -1) {
        fprintf(stderr, "Input too large, would cause overflow\n");
        return EXIT_FAILURE;
    }
    
    if (printf("Maximum number of equilateral triangles: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}