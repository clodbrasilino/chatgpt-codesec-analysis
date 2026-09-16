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
            free_tuple(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;

        char *token = (char *)malloc(span + 1);
        if (token == NULL) {
            free_tuple(tuple);
            free(temp);
            return NULL;
        }
        memcpy(token, ptr, span);
        token[span] = '\0';
        
        tuple->items[tuple->count] = token;
        tuple->count++;

        ptr += span;
        if (*ptr != '\0') {
            ptr += strspn(ptr, delim);
            if (*ptr == '\0') {
                new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
                if (new_items == NULL) {
                    free_tuple(tuple);
                    free(temp);
                    return NULL;
                }
                tuple->items = new_items;
                tuple->items[tuple->count] = strdup("");
                if (tuple->items[tuple->count] == NULL) {
                    free_tuple(tuple);
                    free(temp);
                    return NULL;
                }
                tuple->count++;
            }
        } else if (span == 0) {
            new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
            if (new_items == NULL) {
                free_tuple(tuple);
                free(temp);
                return NULL;
            }
            tuple->items = new_items;
            tuple->items[tuple->count] = strdup("");
            if (tuple->items[tuple->count] == NULL) {
                free_tuple(tuple);
                free(temp);
                return NULL;
            }
            tuple->count++;
        }
    }

    if (tuple->count == 0) {
        char **new_items = (char **)realloc(tuple->items, sizeof(char *));
        if (new_items == NULL) {
            free_tuple(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[tuple->count] = strdup("");
        if (tuple->items[tuple->count] == NULL) {
            free_tuple(tuple);
            free(temp);
            return NULL;
        }
        tuple->count++;
    }

    free(temp);
    return tuple;
}

char *add_char_to_result(char *result, size_t *result_len, size_t *result_cap, char c) {
    if (*result_len + 5 >= *result_cap) {
        *result_cap *= 2;
        char *new_result = (char *)realloc(result, *result_cap);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
    }
    
    if (*result_len > 1) {
        result[*result_len] = ',';
        result[*result_len + 1] = ' ';
        *result_len += 2;
    }
    
    result[*result_len] = '\'';
    result[*result_len + 1] = c;
    result[*result_len + 2] = '\'';
    *result_len += 3;
    result[*result_len] = '\0';
    
    return result;
}

char *format_tuple(Tuple *t) {
    size_t cap = 128;
    size_t len = 1;
    char *result = (char *)malloc(cap);
    if (result == NULL) return NULL;
    result[0] = '[';
    result[1] = '\0';

    for (size_t i = 0; i < t->count; i++) {
        for (size_t j = 0; t->items[i][j] != '\0'; j++) {
            result = add_char_to_result(result, &len, &cap, t->items[i][j]);
            if (result == NULL) return NULL;
        }
    }

    if (len + 2 >= cap) {
        cap = len + 3;
        char *new_result = (char *)realloc(result, cap);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
    }
    result[len] = ']';
    result[len + 1] = '\0';

    return result;
}

int main(void) {
    const char *input1 = "python3.0";
    const char *input2 = "item1";
    const char *delimiter = ".";
    const char *space_delim = " ";

    Tuple *my_tuple1 = string_to_tuple(input1, delimiter);
    if (my_tuple1 != NULL) {
        char *res = format_tuple(my_tuple1);
        if (res != NULL) {
            printf("Test 0: %s\n", res);
            free(res);
        }
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, space_delim);
    if (my_tuple2 != NULL) {
        char *res = format_tuple(my_tuple2);
        if (res != NULL) {
            printf("Test 1: %s\n", res);
            free(res);
        }
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple("15.10", delimiter);
    if (my_tuple3 != NULL) {
        char *res = format_tuple(my_tuple3);
        if (res != NULL) {
            printf("Test 2: %s\n", res);
            free(res);
        }
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}