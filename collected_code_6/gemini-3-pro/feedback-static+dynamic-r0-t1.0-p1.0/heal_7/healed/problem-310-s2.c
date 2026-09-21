#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    Tuple* tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (len == 0) {
        return tuple;
    }

    if (str[0] != '(' || str[len - 1] != ')') {
        tuple->elements = malloc(len * sizeof(char*));
        if (tuple->elements == NULL) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = malloc(2);
            if (tuple->elements[i] != NULL) {
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
            }
        }
        tuple->count = len;
        return tuple;
    }

    if (len < 2) {
        free(tuple);
        return NULL;
    }

    char* str_copy = malloc(len);
    if (str_copy == NULL) {
        free(tuple);
        return NULL;
    }
    
    for (size_t i = 1; i < len - 1; i++) {
        str_copy[i - 1] = str[i];
    }
    str_copy[len - 2] = '\0';

    char* saveptr;
    char* token = strtok_r(str_copy, ",", &saveptr);
    while (token != NULL) {
        while (isspace((unsigned char)*token)) {
            token++;
        }
        
        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        size_t t_len = strlen(token);
        char* end = token + t_len - 1;
        while (end > token && isspace((unsigned char)*end)) {
            end--;
        }
        end[1] = '\0';

        if (end > token && ((*token == '\'' && *end == '\'') || (*token == '"' && *end == '"'))) {
            token++;
            *end = '\0';
        }

        char** new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char*));
        if (new_elements == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->elements = new_elements;

        size_t token_len = strlen(token);
        tuple->elements[tuple->count] = malloc(token_len + 1);
        if (tuple->elements[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        
        strncpy(tuple->elements[tuple->count], token, token_len + 1);
        tuple->count++;

        token = strtok_r(NULL, ",", &saveptr);
    }

    free(str_copy);
    return tuple;
}

void print_tuple_like_list(Tuple* tuple) {
    if (tuple == NULL) {
        return;
    }
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    size_t capacity = 256;
    size_t length = 0;
    char* input = malloc(capacity);
    
    if (input == NULL) {
        return 1;
    }
    
    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* new_input = realloc(input, capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }
            input = new_input;
        }
        input[length++] = (char)c;
    }
    input[length] = '\0';

    if (length > 0) {
        Tuple* tuple = string_to_tuple(input);
        if (tuple != NULL) {
            print_tuple_like_list(tuple);
            free_tuple(tuple);
        }
    }
    
    free(input);
    return 0;
}