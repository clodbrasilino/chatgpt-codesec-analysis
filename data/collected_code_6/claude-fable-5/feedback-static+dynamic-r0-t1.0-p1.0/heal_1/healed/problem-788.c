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
    size_t len;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    len = strnlen(str, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return NULL;
    }

    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->str = malloc(len + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }
    memcpy(t->str, str, len);
    t->str[len] = '\0';

    if (list_size > 0) {
        t->list = malloc(list_size * sizeof(int));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        memcpy(t->list, list, list_size * sizeof(int));
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
    const char *s = "WEB";
    int values[] = {1, 2};
    Tuple *t;

    t = create_tuple(s, values, sizeof(values) / sizeof(values[0]));
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}