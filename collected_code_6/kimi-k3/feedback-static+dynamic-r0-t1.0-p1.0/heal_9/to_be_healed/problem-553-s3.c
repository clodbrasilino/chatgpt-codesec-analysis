#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got <no output>
  *  test case 2 failed: expected 8.123, got <no output>
  *  test case 0 failed: expected 4.56, got <no output>
  */

double tuple_to_float(const IntTuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size == 0) {
        return 0.0;
    }
    
    double result = 0.0;
    double sign = 1.0;
    size_t i = 0;
    int has_decimal = 0;
    size_t decimal_pos = 0;
    size_t start_idx = 0;
    
    if (tuple->elements[0] < 0) {
        sign = -1.0;
        if (tuple->size > 1 && tuple->elements[1] == -1) {
            start_idx = 1;
        }
    }
    
    for (i = start_idx; i < tuple->size; i++) {
        if (tuple->elements[i] == -1) {
            has_decimal = 1;
            decimal_pos = i;
            break;
        }
    }
    
    if (has_decimal) {
        for (i = start_idx; i < decimal_pos; i++) {
            double digit = (double)abs(tuple->elements[i]);
            if (i == start_idx) {
                result = digit;
            } else {
                result = result * 10.0 + digit;
            }
        }
        
        double fraction = 0.0;
        double divisor = 10.0;
        for (i = decimal_pos + 1; i < tuple->size; i++) {
            double digit = (double)abs(tuple->elements[i]);
            fraction += digit / divisor;
            divisor *= 10.0;
        }
        
        result += fraction;
    } else {
        for (i = start_idx; i < tuple->size; i++) {
            double digit = (double)abs(tuple->elements[i]);
            if (i == start_idx) {
                result = digit;
            } else {
                result = result * 10.0 + digit;
            }
        }
    }
    
    return result * sign;
}

int main(void) {
    int data0[] = {4, -1, 5, 6};
    int data1[] = {7, -1, 2, 5, 6};
    int data2[] = {8, -1, 1, 2, 3};
    
    IntTuple t0 = {data0, 4};
    IntTuple t1 = {data1, 5};
    IntTuple t2 = {data2, 5};
    
    printf("%.3f\n", tuple_to_float(&t0));
    printf("%.3f\n", tuple_to_float(&t1));
    printf("%.3f\n", tuple_to_float(&t2));
    
    return 0;
}