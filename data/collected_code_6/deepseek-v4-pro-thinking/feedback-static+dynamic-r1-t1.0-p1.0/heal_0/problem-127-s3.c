#include <stdio.h>
#include <limits.h>
#include <errno.h>

int multiply(int a, int b) {
    long long result = 0;
    long long x = a;
    long long y = b;
    int negative = 0;

    if (x < 0) {
        negative = !negative;
        x = -x;
    }
    if (y < 0) {
        negative = !negative;
        y = -y;
    }

    while (y > 0) {
        if (y & 1) {
            result += x;
        }
        y >>= 1;
        if (y > 0) {
            x <<= 1;
        }
    }

    if (negative) {
        result = -result;
    }

    if (result > INT_MAX || result < INT_MIN) {
        errno = ERANGE;
        return 0;
    }

    return (int)result;
}

int main(void) {
    printf("%d\n", multiply(7, 8));
    printf("%d\n", multiply(-7, 8));
    printf("%d\n", multiply(7, -8));
    printf("%d\n", multiply(-7, -8));
    printf("%d\n", multiply(INT_MAX, 1));
    printf("%d\n", multiply(INT_MIN, 1));
    return 0;
}