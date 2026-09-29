#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Tuple {
    int whole;
    int fractional;
    bool is_negative;
};

double tuple_to_double(const struct Tuple* t) {
    if (!t) {
        return 0.0;
    }

    double result = (double)t->whole;
    
    int temp = t->fractional;
    double divisor = 1.0;
    
    while (temp > 0) {
        divisor *= 10.0;
        temp /= 10;
    }
    
    if (divisor > 1.0) {
        result += (double)t->fractional / divisor;
    }
    
    if (t->is_negative) {
        result = -result;
    }
    
    return result;
}

int main(void) {
    struct Tuple t1 = {5, 25, false};
    struct Tuple t2 = {10, 5, true};
    struct Tuple t3 = {0, 99, false};

    printf("%f\n", tuple_to_double(&t1));
    printf("%f\n", tuple_to_double(&t2));
    printf("%f\n", tuple_to_double(&t3));

    return 0;
}