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

static int checked_memcpy(void *dst, size_t dst_capacity, const void *src, size_t copy_len)
{
    if (dst == NULL || (src == NULL && copy_len > 0)) {
        return -1;
    }

    if (copy_len > dst_capacity) {
        return -1;
    }

    if (copy_len > 0) {
        memcpy(dst, src, copy_len);
    }

    return 0;
}

Tuple *create_tuple(const char *str, const int *list, size_t list_size)
{
    Tuple *t;
    size_t str_len;
    size_t str_capacity;
    size_t list_bytes;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    str_len = bounded_strnlen(str, MAX_STRING_LENGTH + 1u);
    if (str_len > MAX_STRING_LENGTH) {
        return NULL;
    }

    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    str_capacity = str_len + 1u;
    list_bytes = list_size * sizeof(int);

    t = malloc(sizeof(*t));
    if (t == NULL) {
        return NULL;
    }

    t->str = NULL;
    t->list = NULL;
    t->list_size = 0;

    t->str = malloc(str_capacity);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }

    if (checked_memcpy(t->str, str_capacity, str, str_len) != 0) {
        free(t->str);
        free(t);
        return NULL;
    }
    t->str[str_len] = '\0';

    if (list_size > 0) {
        t->list = malloc(list_bytes);
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }

        if (checked_memcpy(t->list, list_bytes, list, list_bytes) != 0) {
            free(t->list);
            free(t->str);
            free(t);
            return NULL;
        }
        t->list_size = list_size;
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
    size_t i;

    if (t == NULL) {
        printf("(null)\n");
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