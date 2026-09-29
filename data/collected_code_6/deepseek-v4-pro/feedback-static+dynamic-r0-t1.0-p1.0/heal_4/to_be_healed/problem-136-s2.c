#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ERR_INVALID_UNITS -1
#define ERR_INVALID_TYPE -2
#define MIN_BILL_AMOUNT 50.0

double calculate_bill(int units, char customer_type) {
    double amount = 0.0;

    if (units < 0) {
        return ERR_INVALID_UNITS;
    }

    switch (customer_type) {
        case 'R':
            if (units <= 100) {
                amount = units * 2.50;
            } else if (units <= 300) {
                amount = 100 * 2.50 + (units - 100) * 4.00;
            } else {
                amount = 100 * 2.50 + 200 * 4.00 + (units - 300) * 5.00;
            }
            break;

        case 'C':
            if (units <= 200) {
                amount = units * 4.00;
            } else if (units <= 500) {
                amount = 200 * 4.00 + (units - 200) * 6.00;
            } else {
                amount = 200 * 4.00 + 300 * 6.00 + (units - 500) * 8.00;
            }
            break;

        case 'I':
            if (units <= 500) {
                amount = units * 6.00;
            } else {
                amount = 500 * 6.00 + (units - 500) * 10.00;
            }
            break;

        default:
            return ERR_INVALID_TYPE;
    }

    if (amount < MIN_BILL_AMOUNT) {
        amount = MIN_BILL_AMOUNT;
    }

    return amount;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    char customer_type;
    long input_units;
    double bill;
    size_t len;

    printf("Enter customer type (R=Residential, C=Commercial, I=Industrial): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(buffer, "\n");
    if (len >= sizeof(buffer) || buffer[len] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid customer type input\n");
        return EXIT_FAILURE;
    }
    buffer[len] = '\0';

    if (len != 1) {
        fprintf(stderr, "Invalid customer type input\n");
        return EXIT_FAILURE;
    }
    customer_type = buffer[0];

    if (customer_type != 'R' && customer_type != 'C' && customer_type != 'I') {
        fprintf(stderr, "Invalid customer type\n");
        return EXIT_FAILURE;
    }

    printf("Enter units consumed: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(buffer, "\n");
    if (len >= sizeof(buffer) || buffer[len] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid units input\n");
        return EXIT_FAILURE;
    }
    buffer[len] = '\0';

    if (len == 0) {
        fprintf(stderr, "Invalid units input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input_units = strtol(buffer, &endptr, 10);
    if (errno == ERANGE || input_units > INT_MAX || input_units < 0) {
        fprintf(stderr, "Invalid units input\n");
        return EXIT_FAILURE;
    }
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid units input\n");
        return EXIT_FAILURE;
    }

    bill = calculate_bill((int)input_units, customer_type);

    if (bill == ERR_INVALID_UNITS) {
        fprintf(stderr, "Units cannot be negative\n");
        return EXIT_FAILURE;
    }

    if (bill == ERR_INVALID_TYPE) {
        fprintf(stderr, "Invalid customer type\n");
        return EXIT_FAILURE;
    }

    printf("Electricity Bill: $%.2f\n", bill);

    return EXIT_SUCCESS;
}