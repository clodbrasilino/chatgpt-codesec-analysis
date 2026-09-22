#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size);
void free_tuple(Tuple *t);
void print_tuple(const Tuple *t);

Tuple *create_tuple(const char *str, const int *list, size_t list_size)
{
    Tuple *t;
    size_t len;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    t = malloc(sizeof(*t));
    if (t == NULL) {
        return NULL;
    }

    len = strlen(str);
    t->str = malloc(len + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }
    memcpy(t->str, str, len + 1);

    if (list_size > 0) {
        t->list = malloc(list_size * sizeof(*t->list));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        memcpy(t->list, list, list_size * sizeof(*t->list));
    } else {
        t->list = NULL;
    }

    t->list_size = list_size;
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
    size_t i;

    if (t == NULL) {
        return;
    }

    printf("(\"%s\", [", t->str);
    for (i = 0; i < t->list_size; i++) {
        printf("%d", t->list[i]);
        if (i + 1 < t->list_size) {
            printf(", ");
        }
    }
    printf("])\n");
}

int main(void)
{
    const char *str = "hello";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    Tuple *t;

    t = create_tuple(str, list, list_size);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}