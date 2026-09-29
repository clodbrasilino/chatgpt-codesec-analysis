#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
} Tuple3;

int subtract_tuples(const Tuple3 *a, const Tuple3 *b, Tuple3 *result) {
    if (a == NULL || b == NULL || result == NULL) {
        return -1;
    }
    
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    
    return 0;
}

int main(void) {
    Tuple3 tuple1 = {10.5, 20.3, 30.7};
    Tuple3 tuple2 = {5.2, 8.1, 12.4};
    Tuple3 result = {0.0, 0.0, 0.0};
    
    if (subtract_tuples(&tuple1, &tuple2, &result) != 0) {
        fprintf(stderr, "Error: Invalid tuple pointers\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
    
    return EXIT_SUCCESS;
}