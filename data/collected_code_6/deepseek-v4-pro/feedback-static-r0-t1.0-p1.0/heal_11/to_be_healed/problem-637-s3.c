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

static int is_valid_number_string(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 1;
        }
    }
    return 0;
}

static int read_input(const char *prompt, char *buffer, size_t buffer_size, double *value) {
    size_t len;

    printf("%s", prompt);
    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 0;
    }

    len = strnlen(buffer, buffer_size);
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return 0;
    }

    if (!is_valid_number_string(buffer, len)) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    char *endptr;
    errno = 0;
    *value = strtod(buffer, &endptr);
    if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double cost_price, selling_price;
    char *buffer1 = NULL;
    char *buffer2 = NULL;
    size_t buffer_size = 256;

    buffer1 = (char *)malloc(buffer_size);
    if (buffer1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    buffer2 = (char *)malloc(buffer_size);
    if (buffer2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buffer1);
        return EXIT_FAILURE;
    }

    memset(buffer1, 0, buffer_size);
    memset(buffer2, 0, buffer_size);

    if (!read_input("Enter cost price: ", buffer1, buffer_size, &cost_price)) {
        free(buffer1);
        free(buffer2);
        return EXIT_FAILURE;
    }

    if (!read_input("Enter selling price: ", buffer2, buffer_size, &selling_price)) {
        free(buffer1);
        free(buffer2);
        return EXIT_FAILURE;
    }

    int result = check_no_profit_no_loss(cost_price, selling_price);
    if (result == -1) {
        fprintf(stderr, "Prices cannot be negative\n");
        free(buffer1);
        free(buffer2);
        return EXIT_FAILURE;
    }
    if (result == 1) {
        printf("No profit and no loss\n");
    } else {
        printf("There is profit or loss\n");
    }

    free(buffer1);
    free(buffer2);
    return EXIT_SUCCESS;
}