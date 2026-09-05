#include <stdio.h>
#include <stdlib.h>

int calculate_loss(int cost_price, int selling_price, int *loss) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }

    if (cost_price > selling_price) {
        *loss = cost_price - selling_price;
        return 0;
    }

    *loss = 0;
    return 1;
}

int main() {
    int cp, sp, loss;

    cp = 100;
    sp = 80;

    /* Possible weaknesses found:
     *  Calling function 'calculate_loss' returns 0
     *  Condition 'calculate_loss(cp,sp,&loss)==0' is always true [knownConditionTrueFalse]
     *  Condition 'calculate_loss(cp,sp,&loss)==0' is always true
     */
    if (calculate_loss(cp, sp, &loss) == 0) {
        /* Possible weaknesses found:
         *  Uninitialized variable: loss [legacyUninitvar]
         */
        printf("%d\n", loss);
    } else {
        printf("none\n");
    }

    int cp2, sp2, loss2;

    cp2 = 50;
    sp2 = 60;

    /* Possible weaknesses found:
     *  Calling function 'calculate_loss' returns 1
     *  Condition 'calculate_loss(cp2,sp2,&loss2)==0' is always false [knownConditionTrueFalse]
     *  Condition 'calculate_loss(cp2,sp2,&loss2)==0' is always false
     */
    if (calculate_loss(cp2, sp2, &loss2) == 0) {
        printf("%d\n", loss2);
    } else {
        printf("none\n");
    }

    return 0;
}