#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char label[32];
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (tuple_a->value < tuple_b->value) return -1;
    if (tuple_a->value > tuple_b->value) return 1;
    return 0;
}

void sort_tuples_by_float(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

void print_tuples(const Tuple *tuples, size_t count) {
    size_t i;
    for (i = 0; i < count; i++) {
        printf("ID: %d, Value: %.2f, Label: %.31s\n", 
               tuples[i].id, tuples[i].value, tuples[i].label);
    }
}

int main(void) {
    Tuple tuples[] = {
        {1, 3.14f, "pi"},
        {2, 1.41f, "sqrt2"},
        {3, 2.72f, "e"},
        {4, 0.58f, "gamma"},
        {5, 1.62f, "phi"}
    };
    
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    printf("Before sorting:\n");
    print_tuples(tuples, tuple_count);
    
    sort_tuples_by_float(tuples, tuple_count);
    
    printf("\nAfter sorting by float value:\n");
    print_tuples(tuples, tuple_count);
    
    return 0;
}