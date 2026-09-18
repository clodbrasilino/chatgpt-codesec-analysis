#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

long long min_operations(long long a, long long b) {
    unsigned long long ua = (unsigned long long)a;
    unsigned long long ub = (unsigned long long)b;
    unsigned long long diff = a > b ? ua - ub : ub - ua;
    
    unsigned long long ans = (diff / 3) * 2;
    unsigned long long rem = diff % 3;
    
    if (rem == 1) {
        ans += 1;
    } else if (rem == 2) {
        ans += 2; 
    }
    
    return (long long)ans;
}

int main(void) {
    long long a, b;
    
    if (scanf("%lld %lld", &a, &b) == 2) {
        long long result = min_operations(a, b);
        printf("%lld\n", result);
    }
    
    return EXIT_SUCCESS;
}