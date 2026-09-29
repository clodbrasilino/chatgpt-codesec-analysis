/* Possible weaknesses found:
 *  stray '`' in program
 */
```
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *str;
    float num;
} Tuple;

int tupleCompar(const void* a, const void* b) {
    Tuple *tupleA = (Tuple*) a;
    Tuple *tupleB = (Tuple*) b;
    return (tupleA->num > tupleB->num) - (tupleA->num < tupleB->num);
}

void sortTuples(Tuple* tuples, size_t n) {
    qsort(tuples, n, sizeof(Tuple), tupleCompar);
}

int main() {
    Tuple tuples[] = {
        {"tuple1", 1.2},
        {"tuple2", 0.5},
        {"tuple3", 2.6},
        {"tuple4", 1.0},
        {"tuple5", 0.3}
    };
    size_t n = sizeof(tuples)/sizeof(tuples[0]);
    sortTuples(tuples, n);

    for(size_t i=0; i < n; i++) {
        printf("Tuple: %s, Number: %f\n", tuples[i].str, tuples[i].num);
    }

    return 0;
}