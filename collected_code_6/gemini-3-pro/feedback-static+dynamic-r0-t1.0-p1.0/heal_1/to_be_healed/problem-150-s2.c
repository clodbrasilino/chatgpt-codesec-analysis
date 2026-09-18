#include <stdio.h>
#include <stdbool.h>

bool is_in_sequence(long long A, long long B, long long C) {
    if (C == 0) {
        return A == B;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -31111 - 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:37034,execs:21306,op:havoc,rep:2)
     */
    if ((B - A) % C == 0 && (B - A) / C >= 0) {
        return true;
    }
    
    return false;
}

int main(void) {
    long long A, B, C;
    
    if (scanf("%lld %lld %lld", &A, &B, &C) != 3) {
        return 1;
    }
    
    if (is_in_sequence(A, B, C)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}