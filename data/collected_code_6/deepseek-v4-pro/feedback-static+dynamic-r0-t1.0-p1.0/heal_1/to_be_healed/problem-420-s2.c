#include <stdio.h>

long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int even_num = 2 * i;
        long long cube = (long long)even_num * even_num * even_num;
        sum += cube;
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:301,execs:151,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Cube sum of first %d even natural numbers: %lld\n", 
           n, cube_sum_even(n));
    
    return 0;
}