#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

typedef struct {
    double x;
    double y;
} Tuple;

int tuple_exp(const Tuple *base, const Tuple *exp, Tuple *result) {
    if (base == NULL || exp == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }
    
    errno = 0;
    double rx = pow(base->x, exp->x);
    if (errno != 0) {
        return -1;
    }
    
    double ry = pow(base->y, exp->y);
    if (errno != 0) {
        return -1;
    }
    
    result->x = rx;
    result->y = ry;
    
    return 0;
}

int main(int argc, char *argv[]) {
    Tuple base = {2.0, 3.0};
    Tuple exp_val = {3.0, 2.0};
    Tuple result;
    
    if (tuple_exp(&base, &exp_val, &result) != 0) {
        perror("Exponentiation failed");
        return EXIT_FAILURE;
    }
    
    printf("Result: (%f, %f)\n", result.x, result.y);
    
    return EXIT_SUCCESS;
}