#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096u

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

static size_t bounded_strnlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

Tuple *create_tuple(const char *str, const int *list, size_t list_size)
{
    Tuple *t;
    size_t str_len;
    size_t str_capacity;
    size_t list_capacity;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    str_len = bounded_strnlen(str, MAX_STRING_LENGTH + 1u);
    if (str_len > MAX_STRING_LENGTH) {
        return NULL;
    }

    str_capacity = str_len + 1u;
    list_capacity = list_size * sizeof(int);

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->str = malloc(str_capacity);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }

    if (str_len >= str_capacity) {
        free(t->str);
        free(t);
        return NULL;
    }

    memcpy(t->str, str, str_len);
    t->str[str_len] = '\0';

    t->list_size = list_size;
    t->list = NULL;

    if (list_size > 0) {
        t->list = malloc(list_capacity);
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }

        if (list_size > list_capacity / sizeof(int)) {
            free(t->list);
            free(t->str);
            free(t);
            return NULL;
        }

        memcpy(t->list, list, list_capacity);
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