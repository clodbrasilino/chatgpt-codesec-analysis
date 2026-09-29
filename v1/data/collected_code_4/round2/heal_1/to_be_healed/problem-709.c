#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tuple {
    char **keys;
    int *values;
    int length;
};

struct Counter {
    int *counts;
    int length;
};

void countUniqueKeys(struct Tuple* tuple, struct Counter* counter) {
    for(int i = 0; i < tuple->length; i++) {
        int found = 0;
        int key = tuple->values[i];
        for(int j = 0; j < counter->length; j++) {
            if(counter->counts[j] == key) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            /* Possible weaknesses found:
             *  leak of 'counter.counts' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            counter->counts = realloc(counter->counts, (counter->length+1)*sizeof(int));
            if(counter->counts == NULL) {
                printf("Error! Unable to allocate memory\n");
                exit(EXIT_FAILURE);
            }
            counter->counts[counter->length] = key;
            counter->length++;
        }
    }
}

int main() {
    struct Tuple tuple;
    tuple.keys = malloc(sizeof(char*)*3);
    tuple.values = malloc(sizeof(int)*3);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple.values' [CWE-690] [-Wanalyzer-possible-null-dereference]
     *  dereference of possibly-NULL 'tuple.keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple.keys[0] = "Key1"; tuple.values[0] = 10;
    tuple.keys[1] = "Key2"; tuple.values[1] = 20;
    tuple.keys[2] = "Key3"; tuple.values[2] = 10;
    tuple.length = 3;

    struct Counter counter;
    counter.counts = NULL;
    counter.length = 0;

    countUniqueKeys(&tuple, &counter);

    printf("Unique keys count: %d\n", counter.length);

    free(tuple.keys);
    free(tuple.values);
    free(counter.counts);
    
    return 0;
}