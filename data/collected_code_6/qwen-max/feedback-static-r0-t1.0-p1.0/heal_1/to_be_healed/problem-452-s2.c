#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Transaction::amount' is never used. [unusedStructMember]
     */
    int amount;
    int loss;
} Transaction;

char *check_loss(Transaction t) {
    if (t.loss > 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        static char result[12];
        snprintf(result, sizeof(result), "Loss: %d", t.loss);
        return result;
    }
    return "None";
}

int main() {
    Transaction t = {500, 100};
    printf("%s\n", check_loss(t));
    return 0;
}