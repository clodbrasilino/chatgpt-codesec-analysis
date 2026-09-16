#include <stdio.h>
#include <stdlib.h>

int calculate_loss(int cost_price, int selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }

    if (cost_price > selling_price) {
        return cost_price - selling_price;
    }

    return -1;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'cp=100', assigned value is 100
     */
    int cp = 100;
    int sp = 80;

    /* Possible weaknesses found:
     *  Assignment 'loss=calculate_loss(cp,sp)', assigned value is 20
     *  Calling function 'calculate_loss' returns 20
     */
    int loss = calculate_loss(cp, sp);

    /* Possible weaknesses found:
     *  Condition 'loss!=-1' is always true [knownConditionTrueFalse]
     *  Condition 'loss!=-1' is always true
     */
    if (loss != -1) {
        printf("%d\n", loss);
    } else {
        printf("none\n");
    }

    int cp2 = 50;
    int sp2 = 60;

    /* Possible weaknesses found:
     *  Assignment 'loss2=calculate_loss(cp2,sp2)', assigned value is -1
     *  Calling function 'calculate_loss' returns -1
     */
    int loss2 = calculate_loss(cp2, sp2);

    /* Possible weaknesses found:
     *  Condition 'loss2!=-1' is always false
     *  Condition 'loss2!=-1' is always false [knownConditionTrueFalse]
     */
    if (loss2 != -1) {
        printf("%d\n", loss2);
    } else {
        printf("none\n");
    }

    return 0;
}