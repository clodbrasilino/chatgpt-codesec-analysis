#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** tuples;
    int count;
} TupleSet;

void remove_tuples_of_length(TupleSet* ts, int k) {
    int j = 0;

    for (int i = 0; i < ts->count; ++i) {
        if(ts->tuples[i] != NULL && strlen(ts->tuples[i]) != k) {
            ts->tuples[j++] = ts->tuples[i];
        }
        else {
            free(ts->tuples[i]);
            ts->tuples[i] = NULL;
        }
    }

    ts->count = j;
    ts->tuples = realloc(ts->tuples, j * sizeof(char*)); 
    if(ts->tuples == NULL && j != 0) {
        exit(EXIT_FAILURE); 
    }
}

int main() {
    TupleSet ts;
    ts.count = 5;
    ts.tuples = malloc(sizeof(char*) * ts.count);
    if(ts.tuples == NULL){
        exit(EXIT_FAILURE);
    }
    
    ts.tuples[0] = strdup("abc");
    ts.tuples[1] = strdup("defgh");
    ts.tuples[2] = strdup("ijk");
    ts.tuples[3] = strdup("lmn");
    ts.tuples[4] = strdup("opqrstu");

    remove_tuples_of_length(&ts, 3);

    for (int i = 0; i < ts.count; ++i) {
        printf("%s\n", ts.tuples[i]);
    }

    for (int i = 0; i < ts.count; ++i) {
        free(ts.tuples[i]);
    }

    free(ts.tuples);

    return 0;
}