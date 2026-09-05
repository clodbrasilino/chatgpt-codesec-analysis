#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        free(tuple);
    }
}

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

    if (strlen(delim) == 0) {
        size_t len = strlen(str);
        if (len == 0) {
            tuple->items = (char **)malloc(sizeof(char *));
            if (tuple->items == NULL) {
                free_tuple(tuple);
                return NULL;
            }
            tuple->items[0] = (char *)malloc(1);
            if (tuple->items[0] == NULL) {
                free_tuple(tuple);
                return NULL;
            }
            tuple->items[0][0] = '\0';
            tuple->count = 1;
        } else {
            tuple->items = (char **)malloc(len * sizeof(char *));
            if (tuple->items == NULL) {
                free_tuple(tuple);
                return NULL;
            }
            for (size_t i = 0; i < len; i++) {
                tuple->items[i] = (char *)malloc(2);
                if (tuple->items[i] == NULL) {
                    tuple->count = i;
                    free_tuple(tuple);
                    return NULL;
                }
                tuple->items[i][0] = str[i];
                tuple->items[i][1] = '\0';
            }
            tuple->count = len;
        }
        return tuple;
    }

    size_t str_len = strlen(str);
    char *temp = (char *)malloc(str_len + 1);
    if (temp == NULL) {
        free_tuple(tuple);
        return NULL;
    }
    strcpy(temp, str);

    char *token = strtok(temp, delim);
    while (token != NULL) {
        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            free(temp);
            free_tuple(tuple);
            return NULL;
        }
        tuple->items = new_items;

        tuple->items[tuple->count] = (char *)malloc(strlen(token) + 1);
        if (tuple->items[tuple->count] == NULL) {
            tuple->count++;
            free(temp);
            free_tuple(tuple);
            return NULL;
        }
        strcpy(tuple->items[tuple->count], token);
        tuple->count++;

        token = strtok(NULL, delim);
    }

    free(temp);

    if (tuple->count == 0) {
        tuple->items = (char **)malloc(sizeof(char *));
        if (tuple->items == NULL) {
            free_tuple(tuple);
            return NULL;
        }
        tuple->items[0] = (char *)malloc(str_len + 1);
        if (tuple->items[0] == NULL) {
            free_tuple(tuple);
            return NULL;
        }
        strcpy(tuple->items[0], str);
        tuple->count = 1;
    }

    return tuple;
}

int main(void) {
    const char *input0 = "python3.0";
    const char *delim0 = ".";
    Tuple *t0 = string_to_tuple(input0, delim0);
    if (t0 != NULL) {
        printf("[");
        for (size_t i = 0; i < t0->count; i++) {
            printf("'%s'", t0->items[i]);
            if (i < t0->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(t0);
    }

    const char *input1 = "item1";
    const char *delim1 = ",";
    Tuple *t1 = string_to_tuple(input1, delim1);
    if (t1 != NULL) {
        printf("[");
        for (size_t i = 0; i < t1->count; i++) {
            printf("'%s'", t1->items[i]);
            if (i < t1->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(t1);
    }

    const char *input2 = "15.10";
    const char *delim2 = ".";
    Tuple *t2 = string_to_tuple(input2, delim2);
    if (t2 != NULL) {
        printf("[");
        for (size_t i = 0; i < t2->count; i++) {
            printf("'%s'", t2->items[i]);
            if (i < t2->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(t2);
    }

    return EXIT_SUCCESS;
}