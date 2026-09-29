#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_SIZE 1024

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

static size_t bounded_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

Tuple *create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }
    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    size_t str_len = bounded_strlen(str, MAX_STRING_SIZE);
    if (str_len == MAX_STRING_SIZE) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(*t));
    if (t == NULL) {
        return NULL;
    }

    t->str = malloc(str_len + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }
    snprintf(t->str, str_len + 1, "%s", str);

    t->list = NULL;
    t->list_size = list_size;

    if (list_size > 0) {
        t->list = malloc(list_size * sizeof(*t->list));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        for (size_t i = 0; i < list_size; i++) {
            t->list[i] = list[i];
        }
    }

    return t;
}

void destroy_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple("hello", list, list_size);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", t->str);
    printf("List:");
    for (size_t i = 0; i < t->list_size; i++) {
        printf(" %d", t->list[i]);
    }
    printf("\n");

    destroy_tuple(t);
    t = NULL;

    return EXIT_SUCCESS;
}