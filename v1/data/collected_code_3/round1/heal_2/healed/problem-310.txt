#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

Tuple* string_to_tuple(char* str) {
    char *delimiter = " ", *token;
    Tuple* tuple = (Tuple*) malloc(sizeof(Tuple));

    if (tuple == NULL) {
        return NULL;
    }

    tuple->first = NULL;
    tuple->second = NULL;

    if ((token = strtok(str, delimiter)) != NULL) {
        if ((tuple->first = malloc(strlen(token)+1)) != NULL) {
            strcpy(tuple->first, token);

            if ((token = strtok(NULL, delimiter)) != NULL) {
                if ((tuple->second = malloc(strlen(token)+1)) != NULL) {
                   strcpy(tuple->second, token);
                } else {
                   free(tuple->first);
                   free(tuple);
                   tuple = NULL;
                }
            }
        } else {
            free(tuple);
            tuple = NULL;
        }
    } 

    return tuple;
}

int main() {
    char str[] = "Hello World";
    Tuple* tuple = string_to_tuple(str);

    if (tuple != NULL) {
        if(tuple->first != NULL && tuple->second != NULL) {
            printf("First: %s, Second: %s\n", tuple->first, tuple->second);
            free(tuple->first);
            free(tuple->second);
        }
        free(tuple);
    }

    return 0;
}