#include <stdio.h>
#include <stdlib.h>

int* calculate_loss(int cost_price, int selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return NULL;
    }

    if (cost_price > selling_price) {
        int* loss = malloc(sizeof(int));
        if (loss == NULL) {
            return NULL;
        }
        *loss = cost_price - selling_price;
        return loss;
    }

    return NULL;
}

int main() {
    int cp = 100;
    int sp = 80;

    int* loss = calculate_loss(cp, sp);

    if (loss != NULL) {
        printf("%d\n", *loss);
        free(loss);
    } else {
        printf("none\n");
    }

    int cp2 = 50;
    int sp2 = 60;

    /* Possible weaknesses found:
     *  Calling function 'calculate_loss' returns 0
     *  Assignment 'loss2=calculate_loss(cp2,sp2)', assigned value is 0
     */
    int* loss2 = calculate_loss(cp2, sp2);

    /* Possible weaknesses found:
     *  Condition 'loss2!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'loss2!=NULL' is always false
     */
    if (loss2 != NULL) {
        printf("%d\n", *loss2);
        free(loss2);
    } else {
        printf("none\n");
    }

    return 0;
}