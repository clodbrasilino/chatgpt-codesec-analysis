#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

Tuple* concatenate_tuples(Tuple *tuple1, Tuple *tuple2) {
    Tuple *result = malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result->first = malloc(strlen(tuple1->first) + strlen(tuple2->first) + 1);
    result->second = malloc(strlen(tuple1->second) + strlen(tuple2->second) + 1);

    strcpy(result->first, tuple1->first);
    strcat(result->first, tuple2->first);

    strcpy(result->second, tuple1->second);
    strcat(result->second, tuple2->second);

    return result;
}

int main() {
    Tuple tuple1 = {"Hello", "World"};
    Tuple tuple2 = {"Goodbye", "Universe"};

    Tuple *result = concatenate_tuples(&tuple1, &tuple2);

    printf("First: %s\n", result->first);
    printf("Second: %s\n", result->second);

    free(result->first);
    free(result->second);
    free(result);

    return 0;
}