#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

Tuple* string_to_tuple(const char* str, const char* delimiter) {
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t delim_len = strlen(delimiter);
    if (delim_len == 0) {
        return NULL;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    const char* delim_pos = strstr(str, delimiter);

    if (delim_pos == NULL) {
        tuple->first = (char*)malloc(strlen(str) + 1);
        if (tuple->first == NULL) {
            free(tuple);
            return NULL;
        }
        strcpy(tuple->first, str);

        tuple->second = (char*)malloc(1);
        if (tuple->second == NULL) {
            free(tuple->first);
            free(tuple);
            return NULL;
        }
        tuple->second[0] = '\0';
    } else {
        size_t first_len = delim_pos - str;
        tuple->first = (char*)malloc(first_len + 1);
        if (tuple->first == NULL) {
            free(tuple);
            return NULL;
        }
        strncpy(tuple->first, str, first_len);
        tuple->first[first_len] = '\0';

        tuple->second = strdup(delim_pos + delim_len);
        if (tuple->second == NULL) {
            free(tuple->first);
            free(tuple);
            return NULL;
        }
    }

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
        printf("%s\n", t0->second);
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