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
    const char *end = temp + str_len;

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
        
        if (*token != '\0') {
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
        }

        token[token_len] = saved_char;
        token += token_len;

        if (*token == '\0') {
            if (token != end) {
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
        if (*token == '\0' && token <= end) {
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
    const char *delim1 = ".";
    Tuple *t1 = string_to_tuple(input1, delim1);
    if (t1 != NULL) {
        printf("[");
        for (size_t i = 0; i < t1->count; i++) {
            printf("'");
            for (size_t j = 0; t1->items[i][j] != '\0'; j++) {
                printf("%c", t1->items[i][j]);
            }
            printf("'");
            if (i < t1->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_tuple(t1);
    } else {
        printf("<no output>\n");
    }

    const char *input2 = "item1";
    const char *delim2 = "1";
    Tuple *t2 = string_to_tuple(input2, delim2);
    if (t2 != NULL) {
        printf("[");
        for (size_t i = 0; i < t2->count; i++) {
            printf("'");
            for (size_t j = 0; t2->items[i][j] != '\0'; j++) {
                printf("%c", t2->items[i][j]);
            }
            printf("'");
            if (i < t2->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_tuple(t2);
    } else {
        printf("<no output>\n");
    }

    const char *input3 = "1.10";
    const char *delim3 = "1";
    Tuple *t3 = string_to_tuple(input3, delim3);
    if (t3 != NULL) {
        printf("[");
        for (size_t i = 0; i < t3->count; i++) {
            printf("'");
            for (size_t j = 0; t3->items[i][j] != '\0'; j++) {
                printf("%c", t3->items[i][j]);
            }
            printf("'");
            if (i < t3->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_tuple(t3);
    } else {
        printf("<no output>\n");
    }

    return EXIT_SUCCESS;
}