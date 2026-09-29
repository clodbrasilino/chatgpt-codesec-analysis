#include <stdio.h>
#include <stdlib.h>

int check_no_profit_no_loss(int cost_price, int selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int cost_price = 100;
    int selling_price = 100;

    if (argc >= 3) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        cost_price = atoi(argv[1]);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        selling_price = atoi(argv[2]);
    }

    int result = check_no_profit_no_loss(cost_price, selling_price);

    if (result == 1) {
        printf("No profit and no loss.\n");
    } else if (result == 0) {
        printf("Profit or loss occurred.\n");
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}