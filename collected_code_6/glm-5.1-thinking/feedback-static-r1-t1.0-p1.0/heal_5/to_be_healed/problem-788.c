#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, size_t str_len, const int *list, size_t list_len) {
    if (str == NULL) {
        return NULL;
    }

    if (list == NULL && list_len > 0) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    if (str_len == SIZE_MAX) {
        free(t);
        return NULL;
    }

    t->str = malloc(str_len + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->str, str, str_len);
    t->str[str_len] = '\0';

    if (list_len > 0) {
        if (list_len > SIZE_MAX / sizeof(int)) {
            free(t->str);
            free(t);
            return NULL;
        }

        t->list = malloc(list_len * sizeof(int));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->list, list, list_len * sizeof(int));
    } else {
        t->list = NULL;
    }

    t->list_len = list_len;

    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main(void) {
    const char *str = "example";
    size_t str_len = strnlen(str, 256);
    int list[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple(str, str_len, list, len);

    if (t != NULL) {
        free_tuple(t);
    }

    return 0;
}