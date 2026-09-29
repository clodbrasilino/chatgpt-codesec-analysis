#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

int parse_tuple(const char *str, Tuple *tuple) {
    int count = 0;
    const char *p = str;
    
    while (*p) {
        if (*p == ',') count++;
        p++;
    }
    
    tuple->size = count + 1;
    tuple->data = (int *)malloc(tuple->size * sizeof(int));
    
    if (!tuple->data) return 0;
    
    p = str;
    for (int i = 0; i < tuple->size; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        tuple->data[i] = atoi(p);
        while (*p && *p != ',') p++;
        if (*p == ',') p++;
    }
    
    return 1;
}

void maximize_tuples(Tuple *t1, Tuple *t2) {
    if (!t1 || !t2 || !t1->data || !t2->data) return;
    
    int size = (t1->size < t2->size) ? t1->size : t2->size;
    
    for (int i = 0; i < size; i++) {
        if (t2->data[i] > t1->data[i]) {
            t1->data[i] = t2->data[i];
        }
    }
}

void print_tuple(const Tuple *tuple) {
    if (!tuple || !tuple->data) return;
    
    printf("(");
    for (int i = 0; i < tuple->size; i++) {
        printf("%d", tuple->data[i]);
        if (i < tuple->size - 1) printf(", ");
    }
    printf(")\n");
}

void free_tuple(Tuple *tuple) {
    if (!tuple) return;
    
    if (tuple->data) {
        free(tuple->data);
        tuple->data = NULL;
    }
    tuple->size = 0;
}

int main() {
    Tuple tuple1 = {NULL, 0};
    Tuple tuple2 = {NULL, 0};
    
    if (parse_tuple("1, 5, 3, 9", &tuple1) &&
        parse_tuple("2, 4, 8, 6", &tuple2)) {
        
        printf("Before maximization:\n");
        printf("Tuple 1: ");
        print_tuple(&tuple1);
        printf("Tuple 2: ");
        print_tuple(&tuple2);
        
        maximize_tuples(&tuple1, &tuple2);
        
        printf("\nAfter maximization:\n");
        printf("Tuple 1: ");
        print_tuple(&tuple1);
        printf("Tuple 2: ");
        print_tuple(&tuple2);
    }
    
    free_tuple(&tuple1);
    free_tuple(&tuple2);
    
    return 0;
}