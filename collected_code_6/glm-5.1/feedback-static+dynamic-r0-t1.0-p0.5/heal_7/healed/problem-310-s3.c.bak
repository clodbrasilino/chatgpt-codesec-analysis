#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL || delim[0] == '\0') {
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

    char *ptr = temp;
    while (*ptr != '\0') {
        size_t span = strcspn(ptr, delim);
        
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

        char *token = (char *)malloc(span + 1);
        if (token == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        memcpy(token, ptr, span);
        token[span] = '\0';
        
        tuple->items[tuple->count] = token;
        tuple->count++;

        ptr += span;
        if (*ptr != '\0') {
            ptr++;
        }
    }

    if (tuple->count == 0) {
        char **new_items = (char **)realloc(tuple->items, sizeof(char *));
        if (new_items == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[tuple->count] = strdup("");
        if (tuple->items[tuple->count] == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count++;
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
    const char *delimiter = ".";
    const char *space_delim = " ";

    Tuple *my_tuple1 = string_to_tuple(input1, delimiter);
    if (my_tuple1 != NULL) {
        printf("Test 0: [");
        for (size_t i = 0; i < my_tuple1->count; i++) {
            for (size_t j = 0; my_tuple1->items[i][j] != '\0'; j++) {
                if (i > 0 || j > 0) printf(", ");
                printf("'%c'", my_tuple1->items[i][j]);
            }
        }
        printf("]\n");
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, space_delim);
    if (my_tuple2 != NULL) {
        printf("Test 1: [");
        for (size_t i = 0; i < my_tuple2->count; i++) {
            for (size_t j = 0; my_tuple2->items[i][j] != '\0'; j++) {
                if (i > 0 || j > 0) printf(", ");
                printf("'%c'", my_tuple2->items[i][j]);
            }
        }
        printf("]\n");
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple("15.10", delimiter);
    if (my_tuple3 != NULL) {
        printf("Test 2: [");
        for (size_t i = 0; i < my_tuple3->count; i++) {
            for (size_t j = 0; my_tuple3->items[i][j] != '\0'; j++) {
                if (i > 0 || j > 0) printf(", ");
                printf("'%c'", my_tuple3->items[i][j]);
            }
        }
        printf("]\n");
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}