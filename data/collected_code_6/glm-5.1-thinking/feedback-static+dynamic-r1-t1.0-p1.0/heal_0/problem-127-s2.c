#include <stdio.h>
#include <limits.h>
#include <errno.h>

int multiply(int a, int b)
{
    long long res = 0;
    long long la = a;
    long long lb = b;
    int sign = 1;

    if (la < 0) {
        sign = -sign;
        la = -la;
    }

    if (lb < 0) {
        sign = -sign;
        lb = -lb;
    }

    while (lb > 0) {
        if (lb & 1) {
            res += la;
        }
        la <<= 1;
        lb >>= 1;
    }

    if (sign < 0) {
        res = -res;
    }

    if (res > INT_MAX || res < INT_MIN) {
        errno = ERANGE;
        return 0;
    }

    return (int)res;
}

int main(void)
{
    printf("%d\n", multiply(5, 7));
    printf("%d\n", multiply(-5, 7));
    printf("%d\n", multiply(0, 7));

    errno = 0;
    int res = multiply(INT_MAX, 2);
    if (errno == ERANGE) {
        printf("Overflow detected\n");
    } else {
        printf("%d\n", res);
    }

    return 0;
}