#include <stdio.h>
#include <stdbool.h>

bool isPresentInSequence(long long d, long long a, long long n) {
    if (d == 0) {
        return (a == n);
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:43716,execs:25330,op:havoc,rep:3)
     */
    if ((n - a) % d == 0) {
        if (d > 0) {
            return (n >= a);
        } else {
            return (n <= a);
        }
    }
    
    return false;
}

int main(void) {
    long long a = 0;
    long long d = 0;
    long long n = 0;
    
    if (scanf("%lld %lld %lld", &a, &d, &n) != 3) {
        return 1;
    }
    
    if (isPresentInSequence(d, a, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}