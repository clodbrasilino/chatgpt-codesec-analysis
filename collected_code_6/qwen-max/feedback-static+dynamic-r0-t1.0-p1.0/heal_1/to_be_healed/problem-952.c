#include <stdio.h>
#include <stdlib.h>

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long modInverse(long long n, long long p) {
    return modPow(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 0
  */

long long ncrModP(int n, int r, int p) {
    if (r == 0)
        return 1;
    
    /* Possible weaknesses found:
     * ASan: stack-overflow (AFL crash: id:000002,sig:11,src:000002,time:872,execs:316,op:havoc,rep:4)
     */
    long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
    
    /* Possible weaknesses found:
     * UBSan: index 1199545584 out of bounds for type 'long long[n + 1]' (AFL crash: id:000001,sig:06,src:000002,time:23,execs:19,op:quick,pos:1)
     * ASan: BUS (AFL crash: id:000001,sig:06,src:000002,time:23,execs:19,op:quick,pos:1)
     */
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:14,execs:16,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, r, p;
    printf("Enter the values of n, r, and p: ");
    scanf("%d %d %d", &n, &r, &p);
    
    if (n < 0 || r < 0 || p <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    long long result = ncrModP(n, r, p);
    printf("Value of C(%d, %d) %d is %lld\n", n, r, p, result);
    
    return 0;
}