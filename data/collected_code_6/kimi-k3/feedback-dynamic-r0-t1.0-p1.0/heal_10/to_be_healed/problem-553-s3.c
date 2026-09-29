#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8.123, got <no output>
  *  test case 1 failed: expected 7.256, got <no output>
  *  test case 0 failed: expected 4.56, got <no output>
  */

double tuple_to_float(const IntTuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size == 0) {
        return 0.0;
    }
    
    double result = 0.0;
    double sign = 1.0;
    size_t start = 0;
    
    if (tuple->elements[0] < 0) {
        sign = -1.0;
        start = 1;
    }
    
    if (start >= tuple->size) {
        return 0.0;
    }
    
    result = (double)abs(tuple->elements[start]);
    
    for (size_t i = start + 1; i < tuple->size; i++) {
        double digit = (double)abs(tuple->elements[i]);
        if (digit < 0.0 || digit > 9.0) {
            return 0.0;
        }
        result = result * 10.0 + digit;
    }
    
    double divisor = 1.0;
    for (size_t i = start + 1; i < tuple->size; i++) {
        divisor *= 10.0;
    }
    
    return result * sign / divisor;
}

int main(void) {
    int data1[] = {4, 5, 6};
    int data2[] = {7, 2, 5, 6};
    int data3[] = {8, 1, 2, 3};
    
    IntTuple t1 = {data1, 3};
    IntTuple t2 = {data2, 4};
    IntTuple t3 = {data3, 4};
    
    printf("%.3f\n", tuple_to_float(&t1));
    printf("%.3f\n", tuple_to_float(&t2));
    printf("%.3f\n", tuple_to_float(&t3));
    
    return 0;
}