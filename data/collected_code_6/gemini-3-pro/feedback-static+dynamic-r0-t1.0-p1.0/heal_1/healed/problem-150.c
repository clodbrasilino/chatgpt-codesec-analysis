#include <stdio.h>
#include <stdbool.h>

bool is_in_sequence(long long A, long long B, long long C) {
    if (C == 0) {
        return A == B;
    } else if (C > 0) {
        if (B < A) {
            return false;
        }
        unsigned long long diff = (unsigned long long)B - (unsigned long long)A;
        unsigned long long step = (unsigned long long)C;
        return (diff % step) == 0;
    } else {
        if (B > A) {
            return false;
        }
        unsigned long long diff = (unsigned long long)A - (unsigned long long)B;
        unsigned long long step = -(unsigned long long)C;
        return (diff % step) == 0;
    }
}

int main() {
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