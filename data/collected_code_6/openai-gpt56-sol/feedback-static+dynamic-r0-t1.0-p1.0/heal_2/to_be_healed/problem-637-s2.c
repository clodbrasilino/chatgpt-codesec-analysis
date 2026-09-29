#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int has_no_profit_no_loss(double cost_price, double selling_price)
{
    return cost_price == selling_price;
}

static int parse_amount(const char *text, double *amount)
{
    char *end = NULL;

    errno = 0;
    *amount = strtod(text, &end);

    return errno == 0 && end != text && *end == '\0' && *amount >= 0.0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    double cost_price;
    double selling_price;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <cost_price> <selling_price>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_amount(argv[1], &cost_price) ||
        !parse_amount(argv[2], &selling_price)) {
        fprintf(stderr, "Invalid amount\n");
        return EXIT_FAILURE;
    }

    if (has_no_profit_no_loss(cost_price, selling_price)) {
        puts("No profit and no loss");
    } else {
        puts("Profit or loss occurred");
    }

    return EXIT_SUCCESS;
}