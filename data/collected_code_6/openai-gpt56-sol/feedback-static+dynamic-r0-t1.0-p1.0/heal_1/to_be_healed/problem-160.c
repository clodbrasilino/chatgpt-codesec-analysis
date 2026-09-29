#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int64_t x1;
    int64_t y1;
    int64_t gcd = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

static int solve_diophantine(int64_t a, int64_t b, int64_t n,
                             int64_t *x, int64_t *y)
{
    if (x == NULL || y == NULL || (a == 0 && b == 0)) {
        return 0;
    }

    int64_t x0;
    int64_t y0;
    int64_t gcd = extended_gcd(a, b, &x0, &y0);

    if (gcd == 0 || n % gcd != 0) {
        return 0;
    }

    int64_t factor = n / gcd;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 83 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:3067,execs:1332,op:havoc,rep:13)
     */
    *x = x0 * factor;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -3486341327113802574 * 27 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:1238,execs:538,op:havoc,rep:13)
     * UBSan: signed integer overflow: -12187958883994 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:3067,execs:1332,op:havoc,rep:13)
     */
    *y = y0 * factor;
    return 1;
}

int main(void)
{
    int64_t a;
    int64_t b;
    int64_t n;
    int64_t x;
    int64_t y;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &a, &b, &n) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!solve_diophantine(a, b, n, &x, &y)) {
        puts("No integer solution");
        return 0;
    }

    printf("x = %" PRId64 ", y = %" PRId64 "\n", x, y);
    return 0;
}