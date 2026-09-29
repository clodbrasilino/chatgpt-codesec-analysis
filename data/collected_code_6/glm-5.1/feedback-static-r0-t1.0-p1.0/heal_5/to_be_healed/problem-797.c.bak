#include <stdio.h>
#include <stdlib.h>

long long sum_odd_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (r <= 0) {
        return 0;
    }
    long long first_odd = (l % 2 != 0) ? l : l + 1;
    long long last_odd = (r % 2 != 0) ? r : r - 1;
    if (first_odd > last_odd) {
        return 0;
    }
    long long n = ((last_odd - first_odd) / 2) + 1;
    return n * (first_odd + last_odd) / 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    long long l, r;
    if (argc == 3) {
        l = atoll(argv[1]);
        r = atoll(argv[2]);
    } else {
        if (scanf("%lld %lld", &l, &r) != 2) {
            return 1;
        }
    }
    long long result = sum_odd_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}