#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double numerator;
    double denominator;
} Tuple;

int divide_tuples(const Tuple *tuples, size_t count, double *results) {
    if (tuples == NULL || results == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (tuples[i].denominator == 0.0) {
            return -2; 
        }
        results[i] = tuples[i].numerator / tuples[i].denominator;
    }

    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {10.0, 2.0},
        {15.0, 3.0},
        {7.0, 0.0}, 
        {20.0, 4.0}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    double *results = (double *)malloc(count * sizeof(double));
    if (results == NULL) {
        return EXIT_FAILURE;
    }

    int status = divide_tuples(tuples, count, results);

    if (status == 0) {
        for (size_t i = 0; i < count; ++i) {
            printf("%f / %f = %f\n", tuples[i].numerator, tuples[i].denominator, results[i]);
        }
    } else if (status == -2) {
        printf("Division by zero error.\n");
    } else {
        printf("Invalid arguments.\n");
    }

    free(results);
    
    return (status == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}