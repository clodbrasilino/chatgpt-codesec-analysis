#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return false;
    }
    if (fabs(selling_price - cost_price) < 1e-9) {
        return true;
    }
    return false;
}

int main() {
    double cp, sp;

    if (scanf("%lf %lf", &cp, &sp) == 2) {
        bool result = check_no_profit_no_loss(cp, sp);
        if (result) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    return 0;
}