#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  */

Tuple* string_to_tuple(const char* str, const char* delimiter) {
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t delim_len = strlen(delimiter);

    if (delim_len == 0) {
        return NULL;
    }

    char* str_copy = (char*)malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    strcpy(str_copy, str);

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(str_copy);
        return NULL;
    }

    char* token = strtok(str_copy, delimiter);
    if (token == NULL) {
        free(str_copy);
        free(tuple);
        return NULL;
    }
    
    tuple->first = (char*)malloc(strlen(token) + 1);
    if (tuple->first == NULL) {
        free(str_copy);
        free(tuple);
        return NULL;
    }
    strcpy(tuple->first, token);

    char* rest = strtok(NULL, delimiter);
    if (rest == NULL) {
        tuple->second = (char*)malloc(1);
        if (tuple->second == NULL) {
            free(tuple->first);
            free(str_copy);
            free(tuple);
            return NULL;
        }
        tuple->second[0] = '\0';
    } else {
        tuple->second = (char*)malloc(strlen(rest) + 1);
        if (tuple->second == NULL) {
            free(tuple->first);
            free(str_copy);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->second, rest);
    }

    free(str_copy);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        free(tuple);
    }
}

int main(void) {
    Tuple* t0 = string_to_tuple("python3.0", ".");
    if (t0 != NULL) {
        printf("%s\n", t0->first);
        free_tuple(t0);
    }

    Tuple* t1 = string_to_tuple("item1", "1");
    if (t1 != NULL) {
        printf("%s\n", t1->first);
        free_tuple(t1);
    }

    Tuple* t2 = string_to_tuple("15.10", ".");
    if (t2 != NULL) {
        printf("%s\n", t2->second);
        free_tuple(t2);
    }

    return 0;
}