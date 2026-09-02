#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple* create_tuple(const char *s, const int *l, size_t list_size) {
    Tuple *new_tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!new_tuple) return NULL;

    new_tuple->str = strdup(s);
    if (!new_tuple->str) {
        free(new_tuple);
        return NULL;
    }

    new_tuple->list = (int *)malloc(list_size * sizeof(int));
    if (!new_tuple->list) {
        free(new_tuple->str);
        free(new_tuple);
        return NULL;
    }
    for (size_t i = 0; i < list_size; ++i) {
        new_tuple->list[i] = l[i];
    }
    new_tuple->list_size = list_size;

    return new_tuple;
}

void free_tuple(Tuple *t) {
    if (t) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main() {
    const char *str = "example string";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = create_tuple(str, list, list_size);
    if (tuple) {
        printf("Tuple created: %s [", tuple->str);
        for (size_t i = 0; i < tuple->list_size; ++i) {
            printf("%d", tuple->list[i]);
            if (i < tuple->list_size - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}