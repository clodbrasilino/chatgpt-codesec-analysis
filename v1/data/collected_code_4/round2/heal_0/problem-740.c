#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

void createKeyValuePairs(char **tupleArray, int tupleSize, KeyValue **keyValuePairs) {
    *keyValuePairs = (KeyValue*) malloc(sizeof(KeyValue) * tupleSize/2);
    if(*keyValuePairs == NULL) {
        fprintf(stderr, "Error! memory not allocated.");
        exit(1);
    }

    for(int i = 0; i < tupleSize; i+=2) {
        if(tupleArray[i] == NULL || tupleArray[i+1] == NULL) {
            fprintf(stderr, "Error! Null value in tuple.");
            free(*keyValuePairs);
            exit(1);
        }

        (*keyValuePairs)[i/2].key = tupleArray[i];
        (*keyValuePairs)[i/2].value = tupleArray[i+1];
    }
}

int main() {
    char *tuple[] = {"1", "one", "2", "two", "3", "three"};
    int tupleSize = sizeof(tuple) / sizeof(tuple[0]);
    KeyValue *keyValuePairs = NULL;

    createKeyValuePairs(tuple, tupleSize, &keyValuePairs);

    for(int i = 0; i < tupleSize/2; i++) {
        printf("%s: %s\n", keyValuePairs[i].key, keyValuePairs[i].value);
    }

    free(keyValuePairs);

    return 0;
}