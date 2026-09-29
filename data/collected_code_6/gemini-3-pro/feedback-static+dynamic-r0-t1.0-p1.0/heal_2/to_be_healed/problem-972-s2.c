#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
} Tuple;

typedef struct {
    Tuple tuple1;
    Tuple tuple2;
} NestedTuple;

NestedTuple* concatenate_tuples(const Tuple* t1, const Tuple* t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }

    NestedTuple* nested = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (nested == NULL) {
        return NULL;
    }

    nested->tuple1.id = t1->id;
    snprintf(nested->tuple1.name, sizeof(nested->tuple1.name), "%s", t1->name);

    nested->tuple2.id = t2->id;
    snprintf(nested->tuple2.name, sizeof(nested->tuple2.name), "%s", t2->name);

    return nested;
}

int main(void) {
    Tuple t1 = {1, "First"};
    Tuple t2 = {2, "Second"};

    NestedTuple* result = concatenate_tuples(&t1, &t2);
    if (result != NULL) {
        printf("NestedTuple: { { %d, %s }, { %d, %s } }\n",
               result->tuple1.id, result->tuple1.name,
               result->tuple2.id, result->tuple2.name);
        
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuples.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}