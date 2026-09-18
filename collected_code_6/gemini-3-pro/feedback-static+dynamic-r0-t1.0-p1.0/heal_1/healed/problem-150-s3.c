#include <stdio.h>
#include <stdbool.h>

bool isPresentInSequence(long long d, long long a, long long n) {
    if (d == 0) {
        return (a == n);
    }
    
    if (d > 0) {
        if (n < a) {
            return false;
        }
        unsigned long long diff = (unsigned long long)n - (unsigned long long)a;
        return (diff % (unsigned long long)d) == 0;
    } else {
        if (n > a) {
            return false;
        }
        unsigned long long diff = (unsigned long long)a - (unsigned long long)n;
        unsigned long long abs_d = -(unsigned long long)d;
        return (diff % abs_d) == 0;
    }
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