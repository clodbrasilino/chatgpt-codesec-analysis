#include <stdio.h>
#include <stdlib.h>

#define ERR_INVALID_UNITS -1
#define ERR_INVALID_TYPE -2

double calculate_bill(int units, char customer_type) {
    double amount = 0.0;

    if (units < 0) {
        return ERR_INVALID_UNITS;
    }

    if (customer_type != 'R' && customer_type != 'C' && customer_type != 'I') {
        return ERR_INVALID_TYPE;
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

    if (amount < 50.0) {
        amount = 50.0;
    }

    return amount;
}

int main(void) {
    int units;
    char customer_type;
    double bill;
    char buffer[256];
    char *endptr;

    printf("Enter customer type (R=Residential, C=Commercial, I=Industrial): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (buffer[0] == '\n' || buffer[1] != '\n') {
        fprintf(stderr, "Invalid customer type input\n");
        return EXIT_FAILURE;
    }
    customer_type = buffer[0];

    printf("Enter units consumed: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    units = (int)strtol(buffer, &endptr, 10);
    if (endptr == buffer || *endptr != '\n' || units < 0) {
        fprintf(stderr, "Invalid units input\n");
        return EXIT_FAILURE;
    }

    bill = calculate_bill(units, customer_type);

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