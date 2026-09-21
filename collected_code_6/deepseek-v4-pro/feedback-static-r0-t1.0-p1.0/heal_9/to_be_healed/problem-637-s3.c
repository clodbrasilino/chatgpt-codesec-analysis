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
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;

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
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) break;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer1[128];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer2[128];

    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));

    if (!read_input("Enter cost price: ", buffer1, sizeof(buffer1), &cost_price)) {
        return EXIT_FAILURE;
    }

    if (!read_input("Enter selling price: ", buffer2, sizeof(buffer2), &selling_price)) {
        return EXIT_FAILURE;
    }

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