#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_len) {
    if (str == NULL) {
        return NULL;
    }

    if (list == NULL && list_len > 0) {
        return NULL;
    }

    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    int str_len = snprintf(NULL, 0, "%s", str);
    if (str_len < 0) {
        free(t);
        return NULL;
    }

    t->str = (char *)malloc((size_t)str_len + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }

    snprintf(t->str, (size_t)str_len + 1, "%s", str);

    if (list_len > 0) {
        if (list_len > SIZE_MAX / sizeof(int)) {
            free(t->str);
            free(t);
            return NULL;
        }

        size_t alloc_size = list_len * sizeof(int);
        t->list = (int *)malloc(alloc_size);
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }

        for (size_t i = 0; i < list_len; i++) {
            t->list[i] = list[i];
        }
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
    int list[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple(str, list, len);

    if (t != NULL) {
        free_tuple(t);
    }

    return 0;
}