#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int loss;
} Transaction;

char *check_loss(Transaction t) {
    if (t.loss > 0) {
        char *result = (char *)malloc(20 * sizeof(char));
        if (result == NULL) return "None";
        snprintf(result, 20, "Loss: %d", t.loss);
        return result;
    }
    return "None";
}

int main() {
    Transaction t = {100};
    char *loss_message = check_loss(t);
    printf("%s\n", loss_message);

    if (strcmp(loss_message, "None") != 0) free(loss_message);

    return 0;
}