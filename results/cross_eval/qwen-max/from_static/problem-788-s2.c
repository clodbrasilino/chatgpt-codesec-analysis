#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple* create_tuple(const char *str, const int *lst, size_t lst_size) {
    if (str == NULL || lst == NULL || lst_size == 0) return NULL;

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) return NULL;

    tuple->string = strdup(str);
    if (tuple->string == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->list = (int *)malloc(lst_size * sizeof(int));
    if (tuple->list == NULL) {
        free(tuple->string);
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < lst_size; ++i) {
        tuple->list[i] = lst[i];
    }

    tuple->list_size = lst_size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->string);
        free(tuple->list);
        free(tuple);
    }
}

int main() {
    const char *str = "example";
    int lst[] = {1, 2, 3};
    size_t lst_size = sizeof(lst) / sizeof(lst[0]);

    Tuple *t = create_tuple(str, lst, lst_size);
    if (t != NULL) {
        printf("Tuple: %s, List: ", t->string);
        for (size_t i = 0; i < t->list_size; ++i) {
            printf("%d, ", t->list[i]);
        }
        printf("\n");
        free_tuple(t);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}