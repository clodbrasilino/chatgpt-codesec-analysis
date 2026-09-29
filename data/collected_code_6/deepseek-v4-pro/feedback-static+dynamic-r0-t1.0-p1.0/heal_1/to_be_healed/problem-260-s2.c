#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long long nsw_prime(int n) {
    if (n <= 0) return -1;
    long long a = 1;
    long long b = 1;
    int count = 0;
    long long candidate = 1;
    while (count < n) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6444863157127625798 + 4612199207062875081 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:216,execs:129,op:havoc,rep:2)
         * UBSan: signed integer overflow: 2 * 6882627592338442563 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:216,execs:129,op:havoc,rep:2)
         */
        long long next = 2 * b + a;
        a = b;
        b = next;
        if (is_prime(next)) {
            count++;
            candidate = next;
        }
    }
    return candidate;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", nsw_prime(n));
    return EXIT_SUCCESS;
}