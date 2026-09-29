#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size)
{
    Tuple *t;
    size_t str_len;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    str_len = strlen(str);
    if (str_len == SIZE_MAX) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->str = malloc(str_len + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }
    memcpy(t->str, str, str_len + 1);

    t->list_size = list_size;
    t->list = NULL;

    if (list_size > 0) {
        t->list = malloc(list_size * sizeof(int));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        memcpy(t->list, list, list_size * sizeof(int));
    }

    return t;
}

void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

void print_tuple(const Tuple *t)
{
    if (t == NULL) {
        printf("(null)\n");
        return;
    }

    printf("(\"%s\", [", t->str);
    for (size_t i = 0; i < t->list_size; i++) {
        printf("%d", t->list[i]);
        if (i + 1 < t->list_size) {
            printf(", ");
        }
    }
    printf("])\n");
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    Tuple *t = create_tuple("example", numbers, size);

    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}