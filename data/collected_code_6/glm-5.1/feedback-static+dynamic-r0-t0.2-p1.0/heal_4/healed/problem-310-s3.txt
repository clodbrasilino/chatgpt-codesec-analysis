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

    Tuple *tuple = malloc(sizeof(Tuple));
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

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);
    while (token != NULL) {
        char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
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
        
        size_t len = strlen(token);
        tuple->items[tuple->count] = malloc(len + 1);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        for (size_t i = 0; i <= len; i++) {
            tuple->items[tuple->count][i] = token[i];
        }

        tuple->count++;
        token = strtok_r(NULL, delim, &rest);
    }

    if (tuple->count == 0) {
        char **new_items = realloc(tuple->items, sizeof(char *));
        if (new_items == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[0] = strdup(str);
        if (tuple->items[0] == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count = 1;
    }

    free(temp);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main(void) {
    const char *input1 = "python3.0";
    const char *input2 = "item1";
    const char *input3 = "1.5.10";
    const char *delim = ".";

    Tuple *my_tuple1 = string_to_tuple(input1, delim);
    if (my_tuple1 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple1->count; i++) {
            printf("'%s'", my_tuple1->items[i]);
            if (i < my_tuple1->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delim);
    if (my_tuple2 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple2->count; i++) {
            printf("'%s'", my_tuple2->items[i]);
            if (i < my_tuple2->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple(input3, delim);
    if (my_tuple3 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple3->count; i++) {
            printf("'%s'", my_tuple3->items[i]);
            if (i < my_tuple3->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}