#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    float val_a = ((const Tuple *)a)->value;
    float val_b = ((const Tuple *)b)->value;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {3, 3.14f},
        {1, 2.71f},
        {2, 1.41f}
    };
    
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    
    for (size_t i = 0; i < count; ++i) {
        printf("%d %f\n", tuples[i].id, tuples[i].value);
    }
    
    return 0;
}