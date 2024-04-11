#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

Tuple* string_to_tuple(char *str) {
    char *delimiter = ",";
    char *token;
    Tuple *tuple = malloc(sizeof(Tuple));

    token = strtok(str, delimiter);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple->first = malloc(strlen(token) + 1);
    strcpy(tuple->first, token);

    token = strtok(NULL, delimiter);
    tuple->second = malloc(strlen(token) + 1);
    strcpy(tuple->second, token);

    return tuple;
}

int main() {
    char str[] = "Hello,World";
    Tuple *tuple = string_to_tuple(str);

    printf("First: %s\n", tuple->first);
    printf("Second: %s\n", tuple->second);

    free(tuple->first);
    free(tuple->second);
    free(tuple);

    return 0;
}