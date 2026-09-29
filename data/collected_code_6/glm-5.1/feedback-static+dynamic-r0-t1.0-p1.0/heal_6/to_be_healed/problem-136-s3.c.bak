#include <stdio.h>
#include <stdlib.h>

double calculate_electricity_bill(int units) {
    if (units < 0) {
        return -1.0;
    }
    double bill = 0.0;
    if (units > 250) {
        bill += (units - 250) * 1.50;
        units = 250;
    }
    if (units > 150) {
        bill += (units - 150) * 0.75;
        units = 150;
    }
    if (units > 50) {
        bill += (units - 50) * 0.50;
        units = 50;
    }
    bill += units * 0.25;
    return bill;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <units>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    double bill = calculate_electricity_bill((int)val);
    if (bill < 0.0) {
        fprintf(stderr, "Error calculating bill\n");
        return EXIT_FAILURE;
    }
    printf("%.2f\n", bill);
    return EXIT_SUCCESS;
}