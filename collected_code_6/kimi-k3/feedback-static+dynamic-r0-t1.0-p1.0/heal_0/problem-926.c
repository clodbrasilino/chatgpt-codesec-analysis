#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t rencontres(uint64_t n, uint64_t k)
{
    if (k > n) {
        return UINT64_C(0);
    }

    if (n == UINT64_C(0)) {
        return UINT64_C(1);
    }

    if (k == n) {
        return UINT64_C(1);
    }

    if (k == UINT64_C(0)) {
        uint64_t result = UINT64_C(1);
        uint64_t sign = UINT64_C(1);

        for (uint64_t i = UINT64_C(1); i <= n; ++i) {
            uint64_t fact = UINT64_C(1);

            for (uint64_t j = UINT64_C(1); j <= i; ++j) {
                if (fact > UINT64_MAX / j) {
                    return UINT64_C(0);
                }
                fact *= j;
            }

            if (sign) {
                if (result > UINT64_MAX - fact) {
                    return UINT64_C(0);
                }
                result += fact;
            } else {
                if (result < fact) {
                    result = UINT64_C(0);
                } else {
                    result -= fact;
                }
            }

            sign = !sign;
        }

        return result;
    }

    uint64_t *prev = (uint64_t *)calloc(n + UINT64_C(1), sizeof(uint64_t));
    uint64_t *curr = (uint64_t *)calloc(n + UINT64_C(1), sizeof(uint64_t));

    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return UINT64_C(0);
    }

    prev[0] = UINT64_C(1);

    for (uint64_t i = UINT64_C(1); i <= n; ++i) {
        for (uint64_t j = UINT64_C(0); j <= i; ++j) {
            if (j == i) {
                curr[j] = UINT64_C(1);
            } else if (j == UINT64_C(0)) {
                uint64_t val = UINT64_C(0);
                uint64_t sign = UINT64_C(1);

                for (uint64_t m = UINT64_C(1); m <= i; ++m) {
                    uint64_t fact = UINT64_C(1);

                    for (uint64_t p = UINT64_C(1); p <= m; ++p) {
                        if (fact > UINT64_MAX / p) {
                            free(prev);
                            free(curr);
                            return UINT64_C(0);
                        }
                        fact *= p;
                    }

                    if (sign) {
                        if (val > UINT64_MAX - fact) {
                            free(prev);
                            free(curr);
                            return UINT64_C(0);
                        }
                        val += fact;
                    } else {
                        if (val < fact) {
                            val = UINT64_C(0);
                        } else {
                            val -= fact;
                        }
                    }

                    sign = !sign;
                }

                curr[j] = val;
            } else {
                uint64_t a = prev[j - UINT64_C(1)];
                uint64_t b = prev[j];

                if (a > UINT64_MAX - b) {
                    free(prev);
                    free(curr);
                    return UINT64_C(0);
                }

                curr[j] = a + b;
            }
        }

        uint64_t *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    uint64_t result = prev[k];

    free(prev);
    free(curr);

    return result;
}

int main(void)
{
    uint64_t n;
    uint64_t k;

    if (scanf("%" SCNu64 "%" SCNu64, &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = rencontres(n, k);

    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}