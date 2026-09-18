#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *element1;
    char *element2;
} Tuple;

Tuple* convertToTuple(char *str, char delim) {
    Tuple *tuple = (Tuple*) malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    char *element1 = strtok(str, &delim);
    char *element2 = strtok(NULL, &delim);
    
    if (!element1 || !element2) {
        free(tuple);
        return NULL;
    }

    tuple->element1 = (char*) malloc(strlen(element1) + 1);
    if (!tuple->element1) {
        free(tuple);
        return NULL;
    }
    strcpy(tuple->element1, element1);

    tuple->element2 = (char*) malloc(strlen(element2) + 1);
    if (!tuple->element2) {
        free(tuple->element1);
        free(tuple);
        return NULL;
    }
    strcpy(tuple->element2, element2);

    return tuple;
}

void freeTuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->element1) {
            free(tuple->element1);
        }
        if (tuple->element2) {
            free(tuple->element2);
        }
        free(tuple);
    }
}

int main() {
    char str[] = "element1;element2";
    Tuple *tuple = convertToTuple(str, ';');

    if(tuple == NULL){
        fprintf(stderr, "String could not be converted to tuple\n");
        return 1;
    }

    printf("Tuple is: (%s, %s)\n", tuple->element1, tuple->element2);

    freeTuple(tuple);
    return 0;
}