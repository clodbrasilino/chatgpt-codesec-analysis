#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int loss;
} Transaction;

char *check_loss(Transaction t) {
    if (t.loss > 0) {
        static char result[12];
        snprintf(result, sizeof(result), "Loss: %d", t.loss);
        return result;
    }
    return "None";
}

int main() {
    Transaction t = {100};
    printf("%s\n", check_loss(t));
    return 0;
}