#include <stdio.h>
#include <stdlib.h>

char *calculate_loss(float amount) {
    if (amount < 0.0f) {
        return "none";
    }
    char *loss = (char *)malloc(20 * sizeof(char));
    if (loss == NULL) {
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(loss, "%.2f", -1 * amount);
    return loss;
}

int main() {
    float amount = -50.25;  // Example input
    char *loss = calculate_loss(amount);
    /* Possible weaknesses found:
     *  String literal compared with variable 'loss'. Did you intend to use strcmp() instead? [literalWithCharPtrCompare]
     */
    if (loss != "none") {
        printf("Loss: %s\n", loss);
        free(loss);
    } else {
        printf("No Loss.\n");
    }
    return 0;
}