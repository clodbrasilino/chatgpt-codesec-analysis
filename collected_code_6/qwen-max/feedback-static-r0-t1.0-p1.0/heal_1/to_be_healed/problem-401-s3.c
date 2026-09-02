#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

Tuple* create_tuple(size_t len) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) exit(1);
    t->data = (int*)malloc(len * sizeof(int));
    if (t->data == NULL) exit(1);
    t->len = len;
    return t;
}

void free_tuple(Tuple *t) {
    /* Possible weaknesses found:
     *  Either the condition 'result!=NULL' is redundant or there is possible null pointer dereference: t. [nullPointerRedundantCheck]
     *  Dereferencing argument t that is null
     *  Null pointer dereference
     *  Null pointer dereference: t [ctunullpointer]
     */
    free(t->data);
    free(t);
}

Tuple* add_tuples(const Tuple *a, const Tuple *b) {
    if (a->len != b->len) return NULL;
    Tuple *result = create_tuple(a->len);
    for (size_t i = 0; i < a->len; ++i) {
        result->data[i] = a->data[i] + b->data[i];
    }
    return result;
}

int main() {
    Tuple *tuple1 = create_tuple(3);
    tuple1->data[0] = 1;
    tuple1->data[1] = 2;
    tuple1->data[2] = 3;

    Tuple *tuple2 = create_tuple(3);
    tuple2->data[0] = 4;
    tuple2->data[1] = 5;
    tuple2->data[2] = 6;

    Tuple *result = add_tuples(tuple1, tuple2);
    /* Possible weaknesses found:
     *  Assuming that condition 'result!=NULL' is not redundant
     */
    if (result != NULL) {
        for (size_t i = 0; i < result->len; ++i) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
    } else {
        printf("Tuples have incompatible lengths\n");
    }

    free_tuple(tuple1);
    free_tuple(tuple2);
    /* Possible weaknesses found:
     *  Calling function free_tuple, 1st argument is null
     *  Calling function 'free_tuple', 1st argument 'result' value is 0
     */
    free_tuple(result);

    return 0;
}