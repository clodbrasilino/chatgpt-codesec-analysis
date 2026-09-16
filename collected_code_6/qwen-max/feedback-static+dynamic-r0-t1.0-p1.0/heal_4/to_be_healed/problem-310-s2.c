#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

Tuple* string_to_tuple(const char* input) {
    char* str = strdup(input);
    if (str == NULL) return NULL;

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
    if (token != NULL) {
        tuple->second = strdup(token);
        if (tuple->second == NULL) {
            free(tuple->first);
            free(tuple);
            free(str);
            return NULL;
        }
    } else {
        tuple->second = NULL;
    }

    free(str);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->first);
        if (tuple->second != NULL) {
            free(tuple->second);
        }
        free(tuple);
    }
}

int main() {
    const char* input1 = "python3.0 is a version";
    Tuple* tuple1 = string_to_tuple(input1);

    const char* input2 = "item1 is an item";
    Tuple* tuple2 = string_to_tuple(input2);

    const char* input3 = "15.10 release";
    Tuple* tuple3 = string_to_tuple(input3);

    if (tuple1 != NULL && tuple1->second != NULL) {
        printf("First: %s, Second: %s\n", tuple1->first, tuple1->second);
        free_tuple(tuple1);
    } else {
        printf("Failed to create tuple for input1.\n");
        free_tuple(tuple1);
    }

    if (tuple2 != NULL && tuple2->second != NULL) {
        printf("First: %s, Second: %s\n", tuple2->first, tuple2->second);
        free_tuple(tuple2);
    } else {
        printf("Failed to create tuple for input2.\n");
        free_tuple(tuple2);
    }

    if (tuple3 != NULL && tuple3->second != NULL) {
        printf("First: %s, Second: %s\n", tuple3->first, tuple3->second);
        free_tuple(tuple3);
    } else {
        printf("Failed to create tuple for input3.\n");
        free_tuple(tuple3);
    }

    return 0;
}