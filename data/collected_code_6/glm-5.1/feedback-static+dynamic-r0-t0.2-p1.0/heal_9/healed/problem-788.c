#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_len) {
    if (str == NULL || (list == NULL && list_len > 0)) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    size_t str_len = strnlen(str, SIZE_MAX);
    t->string = malloc(str_len + 1);
    if (t->string == NULL) {
        free(t);
        return NULL;
    }
    memcpy_s(t->string, str_len + 1, str, str_len + 1);

    if (list_len > 0) {
        if (list_len > SIZE_MAX / sizeof(int)) {
            free(t->string);
            free(t);
            return NULL;
        }
        size_t list_bytes = list_len * sizeof(int);
        t->list = malloc(list_bytes);
        if (t->list == NULL) {
            free(t->string);
            free(t);
            return NULL;
        }
        memcpy_s(t->list, list_bytes, list, list_bytes);
    } else {
        t->list = NULL;
    }

    t->list_len = list_len;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->string);
        free(t->list);
        free(t);
    }
}

int main(void) {
    const char *str = "example";
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    Tuple *t = create_tuple(str, arr, len);
    if (t == NULL) {
        return EXIT_FAILURE;
    }

    printf("String: %s\n", t->string);
    printf("List: ");
    for (size_t i = 0; i < t->list_len; ++i) {
        printf("%d ", t->list[i]);
    }
    printf("\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}