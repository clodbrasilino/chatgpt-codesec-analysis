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

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);
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
        
        tuple->items[tuple->count] = strdup(token);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        tuple->count++;
        token = strtok_r(NULL, delim, &rest);
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
    const char *input3 = "10.5";
    const char *delim = ".";

    Tuple *my_tuple1 = string_to_tuple(input1, delim);
    if (my_tuple1 != NULL) {
        for (size_t i = 0; i < my_tuple1->count; i++) {
            printf("%zu: %s\n", i, my_tuple1->items[i]);
        }
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delim);
    if (my_tuple2 != NULL) {
        for (size_t i = 0; i < my_tuple2->count; i++) {
            printf("%zu: %s\n", i, my_tuple2->items[i]);
        }
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple(input3, delim);
    if (my_tuple3 != NULL) {
        for (size_t i = 0; i < my_tuple3->count; i++) {
            printf("%zu: %s\n", i, my_tuple3->items[i]);
        }
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}