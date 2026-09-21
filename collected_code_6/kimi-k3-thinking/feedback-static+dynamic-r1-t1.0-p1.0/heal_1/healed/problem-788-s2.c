#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

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

    str_len = strnlen(str, MAX_STR_LEN);
    if (str_len == MAX_STR_LEN) {
        return NULL;
    }

    if (list_size > SIZE_MAX / sizeof(int)) {
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

    t->list = NULL;
    t->list_size = list_size;

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

int main(void)
{
    const char *str = "hello";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t i;
    Tuple *t;

    t = create_tuple(str, list, list_size);
    if (t == NULL) {
        fprintf(stderr, "Error: failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple: (\"%s\", [", t->str);
    for (i = 0; i < t->list_size; i++) {
        printf("%d", t->list[i]);
        if (i + 1 < t->list_size) {
            printf(", ");
        }
    }
    printf("])\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}