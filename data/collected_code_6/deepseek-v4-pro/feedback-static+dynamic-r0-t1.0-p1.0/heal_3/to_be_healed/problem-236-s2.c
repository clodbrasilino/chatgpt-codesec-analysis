#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_series(int64_t n) {
    if (n <= 0) {
        return 0;
    }
    if (n % 2 == 0) {
        return (n / 2) * (n + 1);
    } else {
        return n * ((n + 1) / 2);
    }
}

int64_t sum_triangular(int64_t n) {
    if (n <= 0) {
        return 0;
    }
    if (n % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 246913586419753 * 22222224 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:4250,execs:2625,op:havoc,rep:12)
         */
        return n / 2 * (n + 1) * (n + 2) / 3;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 471747370466620 * 30716361 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:615,execs:430,op:havoc,rep:1)
         */
        return n * ((n + 1) / 2) * (n + 2) / 3;
    }
}

int64_t countTriangles(int n) {
    if (n <= 0) {
        return 0;
    }

    int64_t up = sum_triangular(n);

    int64_t m = (n - 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 123456776543210 * 44444445 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:4250,execs:2625,op:havoc,rep:12)
     * UBSan: signed integer overflow: 235873677554220 * 61432721 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:615,execs:430,op:havoc,rep:1)
     */
    int64_t down = m * (m + 1) * (4 * m + 5) / 6;

    int64_t both = 0;
    if (n >= 4) {
        int64_t k = (n - 3) / 2;
        int64_t sum1 = sum_series(k);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 123456754320990 * 22222219 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:4250,execs:2625,op:havoc,rep:12)
         * UBSan: signed integer overflow: 235873646837862 * 30716357 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:615,execs:430,op:havoc,rep:1)
         */
        int64_t sum2 = k * (k + 1) * (2 * k + 1) / 6;
        int64_t sum_tri = (sum1 + sum2) / 2;
        both = 2 * sum_tri;
    }

    return up + down + both;
}

int main(void) {
    int n;

    printf("Enter side length: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }

    int64_t result = countTriangles(n);
    printf("Maximum equilateral triangles: %" PRId64 "\n", result);

    return EXIT_SUCCESS;
}