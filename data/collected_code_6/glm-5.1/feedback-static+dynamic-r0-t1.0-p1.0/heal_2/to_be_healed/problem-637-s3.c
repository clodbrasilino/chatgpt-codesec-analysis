#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return false;
    }
    if (selling_price == cost_price) {
        return true;
    }
    return false;
}

int main() {
    double cp = 100.0;
    double sp = 100.0;
    bool result = check_no_profit_no_loss(cp, sp);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}