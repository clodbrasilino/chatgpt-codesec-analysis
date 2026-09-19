#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct {
    long long high;
    long long low;
} bigint;

bigint add(bigint a, bigint b) {
    bigint result = {0, 0};
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3980154972736918051 + 6440026026380244498 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:721,execs:300,op:havoc,rep:15)
     */
    result.low = a.low + b.low;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5456313900544214763 + 8828501344369052867 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:721,execs:300,op:havoc,rep:15)
     */
    result.high = a.high + b.high + (result.low < a.low);
    return result;
}

bigint lucas_number(int n) {
    if (n == 0) return (bigint){0, 2};
    if (n == 1) return (bigint){0, 1};

    bigint a = {0, 2}, b = {0, 1};
    for (int i = 2; i <= n; ++i) {
        bigint c = add(a, b);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the index of the Lucas number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Index must be non-negative\n");
        return EXIT_FAILURE;
    }

    bigint result = lucas_number(n);
    printf("The %dth Lucas number is: %" PRId64 "%020" PRId64 "\n", n, (int64_t)result.high, (int64_t)result.low);
    return EXIT_SUCCESS;
}