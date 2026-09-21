#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

static int is_valid_number_string(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 1;
        }
        str++;
    }
    return 0;
}

int main(void) {
    double cost_price, selling_price;
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    char *endptr;

    printf("Enter cost price: ");
    read = getline(&input, &len, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    }

    if (read == 0 || !is_valid_number_string(input)) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    cost_price = strtod(input, &endptr);
    if (errno == ERANGE || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Enter selling price: ");
    read = getline(&input, &len, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    }

    if (read == 0 || !is_valid_number_string(input)) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    selling_price = strtod(input, &endptr);
    if (errno == ERANGE || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    input = NULL;
    len = 0;

    int result = check_no_profit_no_loss(cost_price, selling_price);
    if (result == -1) {
        fprintf(stderr, "Prices cannot be negative\n");
        return EXIT_FAILURE;
    }
    if (result == 1) {
        printf("No profit and no loss\n");
    } else {
        printf("There is profit or loss\n");
    }

    return EXIT_SUCCESS;
}