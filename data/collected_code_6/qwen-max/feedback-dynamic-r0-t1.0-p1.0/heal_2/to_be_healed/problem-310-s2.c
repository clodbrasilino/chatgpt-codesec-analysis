#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got ["python","3.0"
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple* string_to_tuple(const char* input) {
    char* str = strdup(input);
    if (str == NULL) {
        return NULL;
    }

    char* token = strtok(str, " ");
    if (token == NULL) {
        free(str);
        return NULL;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(str);
        return NULL;
    }

    tuple->first = strdup(token);
    if (tuple->first == NULL) {
        free(tuple);
        free(str);
        return NULL;
    }

    token = strtok(NULL, " ");
    if (token == NULL) {
        free(tuple->first);
        free(tuple);
        free(str);
        return NULL;
    }

    tuple->second = strdup(token);
    if (tuple->second == NULL) {
        free(tuple->first);
        free(tuple);
        free(str);
        return NULL;
    }

    free(str);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        free(tuple);
    }
}

int main() {
    const char* input = "Hello World";
    Tuple* tuple = string_to_tuple(input);

    if (tuple != NULL) {
        printf("First: %s, Second: %s\n", tuple->first, tuple->second);
        free_tuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}