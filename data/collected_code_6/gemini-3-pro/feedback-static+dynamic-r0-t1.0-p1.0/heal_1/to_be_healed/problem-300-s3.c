#include <stdio.h>
#include <stdlib.h>

long long int calculateCombinations(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;
    
    long long int res = 1;
    if (k > n - k) k = n - k;
    
    for (int i = 0; i < k; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 176504160071359395 * 73 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:227,execs:128,op:havoc,rep:4)
         */
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long int countBinarySequences(int n) {
    if (n < 0) return 0;
    
    long long int total_count = 0;
    for (int k = 0; k <= n; ++k) {
        long long int combinations = calculateCombinations(n, k);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6890268572 * 6890268572 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:227,execs:128,op:havoc,rep:4)
         * UBSan: signed integer overflow: 6646215757681299270 + 4857445984927644900 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:7906,execs:3896,op:havoc,rep:6)
         * UBSan: signed integer overflow: -2154676386599413204 + -7615641896514585536 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:227,execs:128,op:havoc,rep:4)
         */
        total_count += combinations * combinations;
    }
    return total_count;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0) {
        return 1;
    }
    
    long long int result = countBinarySequences(n);
    printf("%lld\n", result);
    
    return 0;
}