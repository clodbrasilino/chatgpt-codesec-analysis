#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

Tuple* string_to_tuple(char *str) {
    Tuple *tuple = malloc(sizeof(Tuple));
    char *token = strtok(str, ",");
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple->first = malloc(strlen(token) + 1);
    strcpy(tuple->first, token);
    token = strtok(NULL, ",");
    tuple->second = malloc(strlen(token) + 1);
    strcpy(tuple->second, token);
    return tuple;
}

int main() {
    char str[] = "Hello,World";
    Tuple *tuple = string_to_tuple(str);
    printf("First: %s, Second: %s\n", tuple->first, tuple->second);
    free(tuple->first);
    free(tuple->second);
    free(tuple);
    return 0;
}