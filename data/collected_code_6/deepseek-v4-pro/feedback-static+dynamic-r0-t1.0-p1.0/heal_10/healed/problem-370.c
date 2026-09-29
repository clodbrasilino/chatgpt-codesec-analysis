#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
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
        char safe_label[33];
        strncpy(safe_label, tuples[i].label, sizeof(tuples[i].label));
        safe_label[sizeof(tuples[i].label) - 1] = '\0';
        printf("ID: %d, Value: %.2f, Label: %s\n", 
               tuples[i].id, tuples[i].value, safe_label);
    }
}

void safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int main(void) {
    Tuple tuples[5];
    
    safe_strncpy(tuples[0].label, "pi", sizeof(tuples[0].label));
    tuples[0].id = 1;
    tuples[0].value = 3.14f;
    
    safe_strncpy(tuples[1].label, "sqrt2", sizeof(tuples[1].label));
    tuples[1].id = 2;
    tuples[1].value = 1.41f;
    
    safe_strncpy(tuples[2].label, "e", sizeof(tuples[2].label));
    tuples[2].id = 3;
    tuples[2].value = 2.72f;
    
    safe_strncpy(tuples[3].label, "gamma", sizeof(tuples[3].label));
    tuples[3].id = 4;
    tuples[3].value = 0.58f;
    
    safe_strncpy(tuples[4].label, "phi", sizeof(tuples[4].label));
    tuples[4].id = 5;
    tuples[4].value = 1.62f;
    
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    printf("Before sorting:\n");
    print_tuples(tuples, tuple_count);
    
    sort_tuples_by_float(tuples, tuple_count);
    
    printf("\nAfter sorting by float value:\n");
    print_tuples(tuples, tuple_count);
    
    return 0;
}