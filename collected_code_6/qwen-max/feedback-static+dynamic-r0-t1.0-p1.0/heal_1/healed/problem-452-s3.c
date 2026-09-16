#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *calculate_loss(float amount) {
    if (amount < 0.0f) {
        return "none";
    }
    char *loss = (char *)malloc(20 * sizeof(char));
    if (loss == NULL) {
        exit(EXIT_FAILURE);
    }
    sprintf(loss, "%.2f", -1 * amount);
    return loss;
}

int main() {
    float amount = -50.25;  // Example input
    char *loss = calculate_loss(amount);

    if (strcmp(loss, "none") != 0) {
        printf("Loss: %s\n", loss);
        free(loss);
    } else {
        printf("No Loss.\n");
    }
    return 0;
}