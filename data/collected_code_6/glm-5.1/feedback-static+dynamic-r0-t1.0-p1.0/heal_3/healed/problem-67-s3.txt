#include <stdio.h>
#include <stdlib.h>

#if __SIZEOF_INT128__ == 16
typedef unsigned __int128 uint128_t;
#else
typedef unsigned long long uint128_t;
#endif

typedef struct {
    uint128_t parts[2];
} u256;

static u256 add_u256(u256 a, u256 b) {
    u256 res;
    res.parts[0] = a.parts[0] + b.parts[0];
    res.parts[1] = a.parts[1] + b.parts[1];
    if (res.parts[0] < a.parts[0]) {
        res.parts[1]++;
    }
    return res;
}

static void print_u256(u256 n) {
    if (n.parts[1] == 0) {
        printf("%llu", (unsigned long long)n.parts[0]);
    } else {
        unsigned long long d = 10000000000000000000ULL;
        unsigned long long r0 = n.parts[0] % d;
        unsigned long long r1 = n.parts[1] % d;
        unsigned long long q0 = n.parts[0] / d;
        unsigned long long q1 = n.parts[1] / d;
        u256 next;
        next.parts[0] = q0 + r1 * (d >> 1) * 2 + q1; 
        next.parts[1] = q1 >> 63;
        print_u256(next);
        printf("%019llu", r0);
    }
}

u256 bell_number(int n) {
    if (n < 0) {
        u256 z = {{0, 0}};
        return z;
    }
    u256 *prev = malloc((n + 2) * sizeof(u256));
    u256 *curr = malloc((n + 2) * sizeof(u256));
    if (!prev || !curr) {
        free(prev);
        free(curr);
        u256 z = {{0, 0}};
        return z;
    }
    prev[0].parts[0] = 1;
    prev[0].parts[1] = 0;
    for (int i = 1; i <= n; i++) {
        curr[0] = prev[i - 1];
        for (int j = 1; j <= i; j++) {
            curr[j] = add_u256(curr[j - 1], prev[j - 1]);
        }
        u256 *tmp = prev;
        prev = curr;
        curr = tmp;
    }
    u256 result = prev[n];
    free(prev);
    free(curr);
    return result;
}

int main(void) {
    print_u256(bell_number(0));
    printf("\n");
    print_u256(bell_number(1));
    printf("\n");
    print_u256(bell_number(10));
    printf("\n");
    print_u256(bell_number(50));
    printf("\n");
    return 0;
}