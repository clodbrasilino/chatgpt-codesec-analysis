#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
} Tuple;

typedef struct {
    Tuple tuple1;
    Tuple tuple2;
} NestedTuple;

char* safe_duplicate(const char* src) {
    if (src == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (src[len] != '\0') {
        len++;
    }
    
    char* dest = (char*)malloc(len + 1);
    if (dest != NULL) {
        for (size_t i = 0; i <= len; i++) {
            dest[i] = src[i];
        }
    }
    return dest;
}

NestedTuple* concatenate_tuples(const Tuple* t1, const Tuple* t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }

    NestedTuple* nested = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (nested == NULL) {
        return NULL;
    }

    nested->tuple1.id = t1->id;
    nested->tuple1.name = safe_duplicate(t1->name);

    nested->tuple2.id = t2->id;
    nested->tuple2.name = safe_duplicate(t2->name);

    if ((t1->name != NULL && nested->tuple1.name == NULL) || 
        (t2->name != NULL && nested->tuple2.name == NULL)) {
        free(nested->tuple1.name);
        free(nested->tuple2.name);
        free(nested);
        return NULL;
    }

    return nested;
}

int main(void) {
    Tuple t1 = {1, "First"};
    Tuple t2 = {2, "Second"};

    NestedTuple* result = concatenate_tuples(&t1, &t2);
    if (result != NULL) {
        printf("NestedTuple: { { %d, %s }, { %d, %s } }\n",
               result->tuple1.id, result->tuple1.name != NULL ? result->tuple1.name : "",
               result->tuple2.id, result->tuple2.name != NULL ? result->tuple2.name : "");
        
        free(result->tuple1.name);
        free(result->tuple2.name);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuples.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}