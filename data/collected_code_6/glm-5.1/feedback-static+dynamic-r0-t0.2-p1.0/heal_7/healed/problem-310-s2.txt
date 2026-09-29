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

    size_t str_len = strlen(str);

    char *temp = (char *)malloc(str_len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

    if (str_len > 0) {
        memcpy(temp, str, str_len + 1);
    } else {
        temp[0] = '\0';
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

        if (token_len > 0) {
            memcpy(tuple->items[tuple->count], token, token_len + 1);
        } else {
            tuple->items[tuple->count][0] = '\0';
        }

        tuple->count++;
        token = strtok_r(NULL, delim, &rest);
    }

    if (tuple->items == NULL && tuple->count == 0) {
        char **new_items = (char **)malloc(sizeof(char *));
        if (new_items != NULL) {
            tuple->items = new_items;
            tuple->items[0] = (char *)malloc(sizeof(char));
            if (tuple->items[0] != NULL) {
                tuple->items[0][0] = '\0';
                tuple->count = 1;
            } else {
                free(tuple->items);
                tuple->items = NULL;
            }
        }
    } else if (tuple->items != NULL && tuple->count == 0) {
        free(tuple->items);
        tuple->items = NULL;
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

    Tuple *my_tuple1 = string_to_tuple(input1, delimiter);
    if (my_tuple1 != NULL) {
        for (size_t i = 0; i < my_tuple1->count; i++) {
            printf("%s\n", my_tuple1->items[i]);
        }
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delimiter);
    if (my_tuple2 != NULL) {
        for (size_t i = 0; i < my_tuple2->count; i++) {
            printf("%s\n", my_tuple2->items[i]);
        }
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple(input3, delimiter);
    if (my_tuple3 != NULL) {
        for (size_t i = 0; i < my_tuple3->count; i++) {
            printf("%s\n", my_tuple3->items[i]);
        }
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}