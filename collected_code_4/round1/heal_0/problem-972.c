#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *element1;
    char *element2;
} tuple;

tuple *concatenateTuples(tuple *tuple1, tuple *tuple2) {
    tuple *nestedTuple = (tuple *)malloc(2 * sizeof(tuple));
    if (nestedTuple == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    
    nestedTuple[0].element1 = strdup(tuple1->element1);
    nestedTuple[0].element2 = strdup(tuple1->element2);
    nestedTuple[1].element1 = strdup(tuple2->element1);
    nestedTuple[1].element2 = strdup(tuple2->element2);

    return nestedTuple;
}

int main() {
    tuple tuple1 = {.element1 = "apple", .element2 = "orange"};
    tuple tuple2 = {.element1 = "banana", .element2 = "grape"};

    tuple *result = concatenateTuples(&tuple1, &tuple2);
    printf("(%s, %s), (%s, %s)\n", result[0].element1, result[0].element2, result[1].element1, result[1].element2);

    free(result[0].element1);
    free(result[0].element2);
    free(result[1].element1);
    free(result[1].element2);
    free(result);

    return 0;
}