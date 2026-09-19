#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

    if (strlen(temp) == 0) {
        free(temp);
        return tuple;
    }

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);
    
    if (token == NULL) {
        char **new_items = (char **)realloc(tuple->items, sizeof(char *));
        if (new_items == NULL) {
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[0] = (char *)malloc(sizeof(char));
        if (tuple->items[0] == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items[0][0] = '\0';
        tuple->count = 1;
        free(temp);
        return tuple;
    }

    while (token != NULL) {
        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        tuple->items = new_items;
        
        size_t token_len = strlen(token);
        tuple->items[tuple->count] = (char *)malloc(token_len + 1);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        strncpy(tuple->items[tuple->count], token, token_len + 1);

        tuple->count++;
        token = strtok_r(NULL, delim, &rest);
    }

    free(temp);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        free(tuple);
    }
}

int main(void) {
    const char *input1 = "python3.0";
    const char *input2 = "item1";
    const char *input3 = "15.10";
    const char *delimiter = ",";

    Tuple *t1 = string_to_tuple(input1, delimiter);
    if (t1 != NULL) {
        for (size_t i = 0; i < t1->count; i++) {
            printf("'%s'\n", t1->items[i]);
        }
        free_tuple(t1);
    }

    Tuple *t2 = string_to_tuple(input2, delimiter);
    if (t2 != NULL) {
        for (size_t i = 0; i < t2->count; i++) {
            printf("'%s'\n", t2->items[i]);
        }
        free_tuple(t2);
    }

    Tuple *t3 = string_to_tuple(input3, delimiter);
    if (t3 != NULL) {
        for (size_t i = 0; i < t3->count; i++) {
            printf("'%s'\n", t3->items[i]);
        }
        free_tuple(t3);
    }

    return EXIT_SUCCESS;
}