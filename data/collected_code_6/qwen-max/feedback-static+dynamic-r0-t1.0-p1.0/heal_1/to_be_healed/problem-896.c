#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compare(const void *p1, const void *p2) {
    /* Possible weaknesses found:
     *  Variable 't1' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *t1 = (Tuple *)p1;
    /* Possible weaknesses found:
     *  Variable 't2' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *t2 = (Tuple *)p2;
    return t1->b - t2->b;
}

void sortTuplesByLastElement(Tuple *tuples, size_t count) {
    qsort(tuples, count, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{3, 5}, {1, 2}, {4, 4}, {2, 3}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    sortTuplesByLastElement(tuples, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d) ", tuples[i].a, tuples[i].b);
    }
    printf("\n");
    
    return 0;
}