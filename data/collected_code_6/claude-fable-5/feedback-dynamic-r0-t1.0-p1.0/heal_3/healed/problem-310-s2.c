#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *items;
    size_t count;
} Tuple;

static Tuple *tuple_create(size_t capacity)
{
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->items = malloc(capacity * sizeof(char));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    t->count = 0;
    return t;
}

static void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}

static Tuple *string_to_tuple(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    Tuple *t = tuple_create(len);
    if (t == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        t->items[i] = str[i];
    }
    t->count = len;

    return t;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < t->count; i++) {
        printf("'%c'", t->items[i]);
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (buffer[0] == '\0') {
            continue;
        }

        Tuple *t = string_to_tuple(buffer);
        if (t == NULL) {
            fprintf(stderr, "Failed to convert string to tuple: \"%s\"\n", buffer);
            return EXIT_FAILURE;
        }

        tuple_print(t);
        fflush(stdout);
        tuple_destroy(t);
    }

    return EXIT_SUCCESS;
}