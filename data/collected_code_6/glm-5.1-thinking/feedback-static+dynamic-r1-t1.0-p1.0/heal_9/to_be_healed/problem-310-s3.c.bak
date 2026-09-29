#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

    if (delim == NULL || delim[0] == '\0') {
        size_t len = strlen(str);
        if (len > 0) {
            tuple->items = malloc(len * sizeof(char *));
            if (tuple->items == NULL) {
                free(tuple);
                return NULL;
            }
            for (size_t i = 0; i < len; i++) {
                tuple->items[i] = malloc(2);
                if (tuple->items[i] == NULL) {
                    for (size_t j = 0; j < i; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tuple);
                    return NULL;
                }
                tuple->items[i][0] = str[i];
                tuple->items[i][1] = '\0';
            }
            tuple->count = len;
        }
    } else {
        size_t delim_len = strlen(delim);
        size_t capacity = 10;
        tuple->items = malloc(capacity * sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
        tuple->count = 0;
        
        const char *start = str;
        const char *end = strstr(start, delim);
        while (end != NULL) {
            size_t token_len = end - start;
            if (tuple->count >= capacity) {
                capacity *= 2;
                char **new_items = realloc(tuple->items, capacity * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t i = 0; i < tuple->count; i++) {
                        free(tuple->items[i]);
                    }
                    free(tuple->items);
                    free(tuple);
                    return NULL;
                }
                tuple->items = new_items;
            }
            tuple->items[tuple->count] = malloc(token_len + 1);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            strncpy(tuple->items[tuple->count], start, token_len);
            tuple->items[tuple->count][token_len] = '\0';
            tuple->count++;
            start = end + delim_len;
            end = strstr(start, delim);
        }
        size_t token_len = strlen(start);
        if (tuple->count >= capacity) {
            capacity += 1;
            char **new_items = realloc(tuple->items, capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            tuple->items = new_items;
        }
        tuple->items[tuple->count] = malloc(token_len + 1);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->items[tuple->count], start);
        tuple->count++;
    }

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    char str_buf[4096] = {0};
    char delim_buf[4096] = {0};

    if (argc >= 3) {
        strncpy(str_buf, argv[1], sizeof(str_buf) - 1);
        strncpy(delim_buf, argv[2], sizeof(delim_buf) - 1);
    } else if (argc == 2) {
        strncpy(str_buf, argv[1], sizeof(str_buf) - 1);
    } else {
        if (fgets(str_buf, sizeof(str_buf), stdin)) {
            str_buf[strcspn(str_buf, "\r\n")] = '\0';
        }
        if (fgets(delim_buf, sizeof(delim_buf), stdin)) {
            delim_buf[strcspn(delim_buf, "\r\n")] = '\0';
        }
    }

    Tuple *t = string_to_tuple(str_buf, delim_buf);
    if (t == NULL) {
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < t->count; i++) {
        printf("'%s'", t->items[i]);
        if (i < t->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free_tuple(t);
    return EXIT_SUCCESS;
}