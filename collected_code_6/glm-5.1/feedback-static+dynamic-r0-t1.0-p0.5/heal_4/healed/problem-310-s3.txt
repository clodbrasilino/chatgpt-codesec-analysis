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

    size_t str_len = 0;
    while (str[str_len] != '\0') {
        str_len++;
    }

    char *temp = (char *)malloc(str_len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }
    for (size_t i = 0; i <= str_len; i++) {
        temp[i] = str[i];
    }

    size_t delim_span = 0;
    while (temp[delim_span] != '\0') {
        const char *d = delim;
        int is_delim = 0;
        while (*d != '\0') {
            if (temp[delim_span] == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (!is_delim) {
            break;
        }
        delim_span++;
    }

    if (delim_span == str_len) {
        char **new_items = (char **)realloc(tuple->items, sizeof(char *));
        if (new_items == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[tuple->count] = (char *)malloc(1);
        if (tuple->items[tuple->count] == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items[tuple->count][0] = '\0';
        tuple->count++;
        free(temp);
        return tuple;
    }

    char *token = strtok(temp, delim);

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
        
        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }
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
        for (size_t i = 0; i <= token_len; i++) {
            tuple->items[tuple->count][i] = token[i];
        }

        tuple->count++;
        token = strtok(NULL, delim);
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
    const char *input2 = "python 3.0";
    const char *delimiter = " ";

    Tuple *my_tuple1 = string_to_tuple(input1, delimiter);
    if (my_tuple1 != NULL) {
        printf("Test 0: [");
        for (size_t i = 0; i < my_tuple1->count; i++) {
            printf("'%s'", my_tuple1->items[i]);
            if (i < my_tuple1->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delimiter);
    if (my_tuple2 != NULL) {
        printf("Test 1: [");
        for (size_t i = 0; i < my_tuple2->count; i++) {
            printf("'%s'", my_tuple2->items[i]);
            if (i < my_tuple2->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple2);
    }

    const char *dot_delim = ".";
    Tuple *my_tuple3 = string_to_tuple("5.10", dot_delim);
    if (my_tuple3 != NULL) {
        printf("Test 2: [");
        for (size_t i = 0; i < my_tuple3->count; i++) {
            printf("'%s'", my_tuple3->items[i]);
            if (i < my_tuple3->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}