#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL || *delim == '\0') {
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
    strcpy(temp, str);

    char *token = temp;
    char *end = temp + str_len;

    while (token <= end) {
        size_t token_len = strcspn(token, delim);

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

        char saved_char = token[token_len];
        token[token_len] = '\0';
        
        tuple->items[tuple->count] = strdup(token);
        if (tuple->items[tuple->count] == NULL) {
            token[token_len] = saved_char;
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count++;

        token[token_len] = saved_char;
        token += token_len;

        if (*token == '\0') {
            if (token == end && str_len > 0 && strspn(end - 1, delim) > 0) {
                char **new_items_end = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
                if (new_items_end == NULL) {
                    for (size_t i = 0; i < tuple->count; i++) {
                        free(tuple->items[i]);
                    }
                    free(tuple->items);
                    free(tuple);
                    free(temp);
                    return NULL;
                }
                tuple->items = new_items_end;
                tuple->items[tuple->count] = strdup("");
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
            }
            break;
        }
        token += strspn(token, delim);
        if (*token == '\0') {
            char **new_items_end = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
            if (new_items_end == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            tuple->items = new_items_end;
            tuple->items[tuple->count] = strdup("");
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
            break;
        }
    }

    free(temp);
    if (tuple->count == 0) {
        free(tuple->items);
        tuple->items = NULL;
    }
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

void print_tuple_as_char_list(Tuple *t) {
    if (t == NULL || t->count == 0) {
        printf("<no output>\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < t->count; i++) {
        printf("'");
        for (size_t j = 0; t->items[i][j] != '\0'; j++) {
            printf("%c", t->items[i][j]);
        }
        printf("'");
        if (i < t->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    const char *input1 = "python3.0";
    const char *delim1 = ".";
    Tuple *t1 = string_to_tuple(input1, delim1);
    print_tuple_as_char_list(t1);
    free_tuple(t1);

    const char *input2 = "item1";
    const char *delim2 = "1";
    Tuple *t2 = string_to_tuple(input2, delim2);
    print_tuple_as_char_list(t2);
    free_tuple(t2);

    const char *input3 = "1.10";
    const char *delim3 = "1";
    Tuple *t3 = string_to_tuple(input3, delim3);
    print_tuple_as_char_list(t3);
    free_tuple(t3);

    return EXIT_SUCCESS;
}