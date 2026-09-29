#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(long long a, long long b, long long c);
bool is_isosceles(long long a, long long b, long long c);

bool is_valid_triangle(long long a, long long b, long long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 166666666666666 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2534,execs:1352,op:havoc,rep:2)
     */
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    }
    return false;
}

bool is_isosceles(long long a, long long b, long long c) {
    if (!is_valid_triangle(a, b, c)) {
        return false;
    }
    return (a == b) || (a == c) || (b == c);
}

int main(void) {
    long long a = 0;
    long long b = 0;
    long long c = 0;

    if (scanf("%lld %lld %lld", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    if (!is_valid_triangle(a, b, c)) {
        printf("Not a valid triangle\n");
        return 1;
    }

    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not isosceles\n");
    }

    return 0;
}