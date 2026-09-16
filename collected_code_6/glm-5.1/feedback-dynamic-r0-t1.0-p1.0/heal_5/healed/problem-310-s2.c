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

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    size_t len = strlen(str);
    if (len == 0) {
        return tuple;
    }

    char *temp = malloc(len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }
    strcpy(temp, str);

    char *token = temp;
    char *next_token = NULL;
    size_t delim_len = strlen(delim);

    while (*token) {
        next_token = strstr(token, delim);
        if (next_token != NULL) {
            size_t t_len = next_token - token;
            if (t_len == 0) {
                char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t i = 0; i < tuple->count; i++) free(tuple->items[i]);
                    free(tuple->items);
                    free(tuple);
                    free(temp);
                    return NULL;
                }
                tuple->items = new_items;
                tuple->items[tuple->count] = malloc(1);
                if (tuple->items[tuple->count] == NULL) {
                    for (size_t i = 0; i < tuple->count; i++) free(tuple->items[i]);
                    free(tuple->items);
                    free(tuple);
                    free(temp);
                    return NULL;
                }
                tuple->items[tuple->count][0] = '\0';
                tuple->count++;
            } else {
                char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t i = 0; i < tuple->count; i++) free(tuple->items[i]);
                    free(tuple->items);
                    free(tuple);
                    free(temp);
                    return NULL;
                }
                tuple->items = new_items;
                tuple->items[tuple->count] = malloc(t_len + 1);
                if (tuple->items[tuple->count] == NULL) {
                    for (size_t i = 0; i < tuple->count; i++) free(tuple->items[i]);
                    free(tuple->items);
                    free(tuple);
                    free(temp);
                    return NULL;
                }
                memcpy(tuple->items[tuple->count], token, t_len);
                tuple->items[tuple->count][t_len] = '\0';
                tuple->count++;
            }
            token = next_token + delim_len;
        } else {
            size_t t_len = strlen(token);
            char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < tuple->count; i++) free(tuple->items[i]);
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            tuple->items = new_items;
            tuple->items[tuple->count] = malloc(t_len + 1);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t i = 0; i < tuple->count; i++) free(tuple->items[i]);
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            strcpy(tuple->items[tuple->count], token);
            tuple->count++;
            break;
        }
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
    const char *delim = ".";

    Tuple *t1 = string_to_tuple(input1, delim);
    if (t1 != NULL) {
        printf("[");
        for (size_t i = 0; i < t1->count; i++) {
            printf("'%s'", t1->items[i]);
            if (i < t1->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(t1);
    }

    Tuple *t2 = string_to_tuple(input2, delim);
    if (t2 != NULL) {
        printf("[");
        for (size_t i = 0; i < t2->count; i++) {
            printf("'%s'", t2->items[i]);
            if (i < t2->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(t2);
    }

    Tuple *t3 = string_to_tuple(input3, delim);
    if (t3 != NULL) {
        printf("[");
        for (size_t i = 0; i < t3->count; i++) {
            printf("'%s'", t3->items[i]);
            if (i < t3->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(t3);
    }

    return EXIT_SUCCESS;
}