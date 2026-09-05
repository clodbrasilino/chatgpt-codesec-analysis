#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define MIN_UNITS 0.0
#define MAX_UNITS 100000.0
#define SLAB1_LIMIT 100.0
#define SLAB2_LIMIT 200.0
#define SLAB3_LIMIT 300.0

#define RATE_SLAB1 1.5
#define RATE_SLAB2 2.5
#define RATE_SLAB3 4.0
#define RATE_SLAB4 6.0
#define FIXED_CHARGE 50.0

typedef enum {
    BILL_SUCCESS = 0,
    BILL_ERROR_INVALID_INPUT,
    BILL_ERROR_OVERFLOW
} BillStatus;

BillStatus calculate_electricity_bill(double units, double *total_bill) {
    double bill_amount = 0.0;
    
    if (total_bill == NULL) {
        return BILL_ERROR_INVALID_INPUT;
    }
    
    if (units < MIN_UNITS || units > MAX_UNITS) {
        return BILL_ERROR_INVALID_INPUT;
    }
    
    if (units <= SLAB1_LIMIT) {
        bill_amount = units * RATE_SLAB1;
    } else if (units <= SLAB2_LIMIT) {
        bill_amount = (SLAB1_LIMIT * RATE_SLAB1) + 
                      ((units - SLAB1_LIMIT) * RATE_SLAB2);
    } else if (units <= SLAB3_LIMIT) {
        bill_amount = (SLAB1_LIMIT * RATE_SLAB1) + 
                      ((SLAB2_LIMIT - SLAB1_LIMIT) * RATE_SLAB2) +
                      ((units - SLAB2_LIMIT) * RATE_SLAB3);
    } else {
        bill_amount = (SLAB1_LIMIT * RATE_SLAB1) + 
                      ((SLAB2_LIMIT - SLAB1_LIMIT) * RATE_SLAB2) +
                      ((SLAB3_LIMIT - SLAB2_LIMIT) * RATE_SLAB3) +
                      ((units - SLAB3_LIMIT) * RATE_SLAB4);
    }
    
    bill_amount += FIXED_CHARGE;
    
    if (bill_amount < 0.0 || bill_amount > (double)INT_MAX) {
        return BILL_ERROR_OVERFLOW;
    }
    
    *total_bill = bill_amount;
    return BILL_SUCCESS;
}

int main(void) {
    double units = 0.0;
    double bill = 0.0;
    BillStatus status;
    int scan_result;
    
    printf("Enter electricity units consumed: ");
    scan_result = scanf("%lf", &units);
    
    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    status = calculate_electricity_bill(units, &bill);
    
    if (status == BILL_ERROR_INVALID_INPUT) {
        fprintf(stderr, "Error: Invalid units value\n");
        return EXIT_FAILURE;
    } else if (status == BILL_ERROR_OVERFLOW) {
        fprintf(stderr, "Error: Bill calculation overflow\n");
        return EXIT_FAILURE;
    } else if (status != BILL_SUCCESS) {
        fprintf(stderr, "Error: Unknown error occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("Total Electricity Bill: Rs. %.2f\n", bill);
    
    return EXIT_SUCCESS;
}