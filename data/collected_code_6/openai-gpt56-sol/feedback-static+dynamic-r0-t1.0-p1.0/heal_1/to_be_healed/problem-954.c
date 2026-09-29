#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

static int calculate_profit(double cost, double revenue, double *profit)
{
    if (profit == NULL || !isfinite(cost) || !isfinite(revenue) ||
        cost < 0.0 || revenue < 0.0 || revenue <= cost) {
        return 0;
    }

    *profit = revenue - cost;
    return isfinite(*profit);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char extra;
    double cost;
    double revenue;
    double profit;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    if (sscanf(input, " %lf %lf %c", &cost, &revenue, &extra) != 2 ||
        errno == ERANGE) {
        return EXIT_FAILURE;
    }

    if (calculate_profit(cost, revenue, &profit)) {
        if (printf("%.2f\n", profit) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("none") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}