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

    const char* delim_pos = strstr(str, delimiter);
    if (delim_pos == NULL) {
        Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
        if (tuple == NULL) {
            return NULL;
        }
        size_t str_len = strlen(str);
        tuple->first = (char*)malloc(str_len + 1);
        if (tuple->first == NULL) {
            free(tuple);
            return NULL;
        }
        memcpy(tuple->first, str, str_len + 1);
        tuple->second = (char*)malloc(1);
        if (tuple->second == NULL) {
            free(tuple->first);
            free(tuple);
            return NULL;
        }
        tuple->second[0] = '\0';
        return tuple;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    size_t first_len = delim_pos - str;
    tuple->first = (char*)malloc(first_len + 1);
    if (tuple->first == NULL) {
        free(tuple);
        return NULL;
    }
    memcpy(tuple->first, str, first_len);
    tuple->first[first_len] = '\0';

    const char* second_start = delim_pos + delim_len;
    size_t second_len = strlen(second_start);
    tuple->second = (char*)malloc(second_len + 1);
    if (tuple->second == NULL) {
        free(tuple->first);
        free(tuple);
        return NULL;
    }
    memcpy(tuple->second, second_start, second_len + 1);

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
    const char* input = "python3.0";
    Tuple* my_tuple = string_to_tuple(input, "3.");
    if (my_tuple != NULL) {
        printf("%s\n", my_tuple->first);
        printf("%s\n", my_tuple->second);
        free_tuple(my_tuple);
    }

    input = "item1";
    my_tuple = string_to_tuple(input, "1");
    if (my_tuple != NULL) {
        printf("%s\n", my_tuple->first);
        printf("%s\n", my_tuple->second);
        free_tuple(my_tuple);
    }

    input = "15.10";
    my_tuple = string_to_tuple(input, ".");
    if (my_tuple != NULL) {
        printf("%s\n", my_tuple->first);
        printf("%s\n", my_tuple->second);
        free_tuple(my_tuple);
    }

    return 0;
}