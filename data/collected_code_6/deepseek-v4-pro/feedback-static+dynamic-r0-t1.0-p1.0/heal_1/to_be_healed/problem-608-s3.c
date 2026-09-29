#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 52
  *  test case 1 failed: expected 5, got 15
  *  test case 0 failed: expected 2, got 5
  */

long long bell_number(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;
    
    long long *bell = (long long *)calloc(n + 1, sizeof(long long));
    if (bell == NULL) return -1;
    
    bell[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        long long prev = bell[0];
        bell[0] = bell[i - 1];
        for (int j = 1; j <= i; j++) {
            long long temp = bell[j];
            bell[j] = prev + bell[j - 1];
            prev = temp;
        }
    }
    
    long long result = bell[n];
    free(bell);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:281,execs:152,op:havoc,rep:10; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = bell_number(n);
    if (result == -1 && n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    
    printf("Bell number B%d = %lld\n", n, result);
    return 0;
}