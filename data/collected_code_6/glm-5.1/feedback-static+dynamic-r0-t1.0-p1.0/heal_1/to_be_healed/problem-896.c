#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compare(const void *x, const void *y) {
    const Tuple *t1 = (const Tuple *)x;
    const Tuple *t2 = (const Tuple *)y;
    return (t1->b > t2->b) - (t1->b < t2->b);
}

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
Tuple *sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return NULL;
    }
    Tuple *result = (Tuple *)malloc(count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        result[i] = tuples[i];
    }
    qsort(result, count, sizeof(Tuple), compare);
    return result;
}

int main(void) {
    Tuple input[] = {{2, 8}, {1, 3}, {5, 2}, {9, 6}};
    size_t count = sizeof(input) / sizeof(input[0]);
    
    Tuple *sorted = sort_tuples(input, count);
    if (sorted == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d)\n", sorted[i].a, sorted[i].b);
    }
    
    free(sorted);
    return 0;
}