#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y, uint64_t *gcd)
{
    __int128 old_r = a;
    __int128 r = b;
    __int128 old_s = 1;
    __int128 s = 0;
    __int128 old_t = 0;
    __int128 t = 1;

    while (r != 0) {
        const __int128 quotient = old_r / r;

        const __int128 next_r = old_r - quotient * r;
        old_r = r;
        r = next_r;

        const __int128 next_s = old_s - quotient * s;
        old_s = s;
        s = next_s;

        const __int128 next_t = old_t - quotient * t;
        old_t = t;
        t = next_t;
    }

    if (old_r < 0) {
        old_r = -old_r;
        old_s = -old_s;
        old_t = -old_t;
    }

    if (old_r > UINT64_MAX ||
        old_s < INT64_MIN || old_s > INT64_MAX ||
        old_t < INT64_MIN || old_t > INT64_MAX) {
        return 0;
    }

    *gcd = (uint64_t)old_r;
    *x = (int64_t)old_s;
    *y = (int64_t)old_t;
    return 1;
}

static int find_solution(int64_t a, int64_t b, int64_t n, int64_t *x, int64_t *y)
{
    int64_t base_x;
    int64_t base_y;
    uint64_t gcd;

    if (x == NULL || y == NULL) {
        return 0;
    }

    if (a == 0 && b == 0) {
        if (n != 0) {
            return 0;
        }
        *x = 0;
        *y = 0;
        return 1;
    }

    if (!extended_gcd(a, b, &base_x, &base_y, &gcd) || gcd == 0) {
        return 0;
    }

    if ((__int128)n % (__int128)gcd != 0) {
        return 0;
    }

    const __int128 multiplier = (__int128)n / (__int128)gcd;
    const __int128 result_x = (__int128)base_x * multiplier;
    const __int128 result_y = (__int128)base_y * multiplier;

    if (result_x < INT64_MIN || result_x > INT64_MAX ||
        result_y < INT64_MIN || result_y > INT64_MAX) {
        return 0;
    }

    *x = (int64_t)result_x;
    *y = (int64_t)result_y;
    return 1;
}

int main(void)
{
    int64_t a;
    int64_t b;
    int64_t n;
    int64_t x;
    int64_t y;

    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &a, &b, &n) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!find_solution(a, b, n, &x, &y)) {
        puts("No representable integer solution");
        return 0;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);
    return 0;
}