#include <stdio.h>
#include <math.h>

#define TRAPEZIUM_SIDES 4

typedef enum {
    TRAPEZIUM_SUCCESS,
    TRAPEZIUM_INVALID_INPUT,
    TRAPEZIUM_NOT_TRAPEZIUM
} TrapeziumStatus;

typedef struct {
    double base1;
    double base2;
    double leg1;
    double leg2;
} Trapezium;

TrapeziumStatus validate_trapezium(const Trapezium *t) {
    if (t == NULL) {
        return TRAPEZIUM_INVALID_INPUT;
    }
    
    if (t->base1 <= 0 || t->base2 <= 0 || t->leg1 <= 0 || t->leg2 <= 0) {
        return TRAPEZIUM_INVALID_INPUT;
    }
    
    if (!isfinite(t->base1) || !isfinite(t->base2) || 
        !isfinite(t->leg1) || !isfinite(t->leg2)) {
        return TRAPEZIUM_INVALID_INPUT;
    }
    
    double base_diff = fabs(t->base1 - t->base2);
    double leg_sum = t->leg1 + t->leg2;
    double leg_diff = fabs(t->leg1 - t->leg2);
    
    if (base_diff >= leg_sum || leg_sum <= leg_diff) {
        return TRAPEZIUM_NOT_TRAPEZIUM;
    }
    
    return TRAPEZIUM_SUCCESS;
}

TrapeziumStatus trapezium_median(const Trapezium *t, double *median) {
    if (median == NULL || t == NULL) {
        return TRAPEZIUM_INVALID_INPUT;
    }
    
    TrapeziumStatus status = validate_trapezium(t);
    if (status != TRAPEZIUM_SUCCESS) {
        return status;
    }
    
    *median = (t->base1 + t->base2) / 2.0;
    
    if (!isfinite(*median)) {
        return TRAPEZIUM_INVALID_INPUT;
    }
    
    return TRAPEZIUM_SUCCESS;
}

int main(void) {
    Trapezium trapezoids[] = {
        {10.0, 6.0, 5.0, 5.0},
        {10.0, 6.0, 3.0, 3.0},
        {0.0, 5.0, 4.0, 4.0},
        {8.0, 4.0, 1.0, 1.0}
    };
    
    double median;
    
    for (int i = 0; i < (int)(sizeof(trapezoids) / sizeof(trapezoids[0])); i++) {
        TrapeziumStatus status = trapezium_median(&trapezoids[i], &median);
        
        printf("Trapezium %d: ", i + 1);
        
        switch (status) {
            case TRAPEZIUM_SUCCESS:
                printf("median = %.2f\n", median);
                break;
            case TRAPEZIUM_INVALID_INPUT:
                printf("invalid input\n");
                break;
            case TRAPEZIUM_NOT_TRAPEZIUM:
                printf("not a valid trapezium\n");
                break;
            default:
                printf("unknown error\n");
                break;
        }
    }
    
    TrapeziumStatus null_status = trapezium_median(NULL, &median);
    if (null_status == TRAPEZIUM_INVALID_INPUT) {
        printf("NULL trapezium handled correctly\n");
    }
    
    /* Possible weaknesses found:
     *  Assignment 'null_median_status=trapezium_median(trapezoids,NULL)', assigned value is 1
     *  Calling function 'trapezium_median' returns 1
     */
    TrapeziumStatus null_median_status = trapezium_median(&trapezoids[0], NULL);
    /* Possible weaknesses found:
     *  Condition 'null_median_status==TRAPEZIUM_INVALID_INPUT' is always true [knownConditionTrueFalse]
     *  Condition 'null_median_status==TRAPEZIUM_INVALID_INPUT' is always true
     */
    if (null_median_status == TRAPEZIUM_INVALID_INPUT) {
        printf("NULL median pointer handled correctly\n");
    }
    
    return 0;
}