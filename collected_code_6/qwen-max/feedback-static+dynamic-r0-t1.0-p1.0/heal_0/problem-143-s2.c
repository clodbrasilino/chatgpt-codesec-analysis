#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type;
    void *value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
} Tuple;

int is_list(void *obj) {
    return ((Tuple *)obj)->count > 0;
}

int count_lists_in_tuple(Tuple *tup) {
    int count = 0;
    for (size_t i = 0; i < tup->count; ++i) {
        if (tup->elements[i].type == 1 && is_list(tup->elements[i].value)) {
            count++;
        }
    }
    return count;
}

int main() {
    // Example usage
    Tuple subtuple1 = {NULL, 0};
    Tuple subtuple2 = {NULL, 0};

    TupleElement element1 = {1, &subtuple1};
    TupleElement element2 = {2, NULL};
    TupleElement element3 = {1, &subtuple2};

    Tuple tuple = {NULL, 0};
    tuple.elements = malloc(3 * sizeof(TupleElement));
    tuple.count = 3;
    tuple.elements[0] = element1;
    tuple.elements[1] = element2;
    tuple.elements[2] = element3;

    int list_count = count_lists_in_tuple(&tuple);
    printf("Number of lists in the tuple: %d\n", list_count);

    free(tuple.elements);
    return 0;
}