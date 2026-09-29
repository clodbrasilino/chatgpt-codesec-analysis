#include <stdio.h>

long long count_rectangles_in_circle(long long r) {
    if (r <= 0) {
        return 0;
    }

    unsigned long long ur = (unsigned long long)r;
    __int128 r_squared = (__int128)ur * ur;
    unsigned long long count = 0;

    for (unsigned long long x = 0; ; ++x) {
        __int128 x_sq = (__int128)(x + 1) * (x + 1);
        if (x_sq > r_squared) {
            break;
        }
        for (unsigned long long y = 0; ; ++y) {
            __int128 y_sq = (__int128)(y + 1) * (y + 1);
            if (x_sq + y_sq > r_squared) {
                break;
            }
            count++;
        }
    }

    return (long long)(count * 4);
}

int main(void) {
    long long r = 0;
    
    if (scanf("%lld", &r) != 1) {
        return 1;
    }

    long long result = count_rectangles_in_circle(r);
    
    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}