#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char **items;
    size_t size;
} Tuple;

Tuple *string_list_to_tuple(const char *const list[], size_t count);
void free_tuple(Tuple *tuple);
void print_tuple(const Tuple *tuple);

static size_t bounded_length(const char *s, size_t max)
{
    size_t len = 0;

    while (len < max && s[len] != '\0') {
        len++;
    }

    return len;
}

int main(void)
{
    const char *list[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = string_list_to_tuple(list, count);

    if (tuple == NULL) {
        fprintf(stderr, "Error: failed to convert string list to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple: ");
    print_tuple(tuple);

    free_tuple(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}

Tuple *string_list_to_tuple(const char *const list[], size_t count)
{
    Tuple *tuple = NULL;

    if (list == NULL || count == 0) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = count;
    tuple->items = calloc(count, sizeof(*tuple->items));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            free_tuple(tuple);
            return NULL;
        }

        len = bounded_length(list[i], MAX_STRING_LENGTH + 1);
        if (len > MAX_STRING_LENGTH) {
            free_tuple(tuple);
            return NULL;
        }

        tuple->items[i] = malloc(len + 1);
        if (tuple->items[i] == NULL) {
            free_tuple(tuple);
            return NULL;
        }

        for (size_t j = 0; j <= len; j++) {
            tuple->items[i][j] = list[i][j];
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }

    free(tuple);
}

void print_tuple(const Tuple *tuple)
{
    if (tuple == NULL) {
        printf("()\n");
        return;
    }

    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("\"%s\"", tuple->items[i] != NULL ? tuple->items[i] : "(null)");
    }
    if (tuple->size == 1) {
        printf(",");
    }
    printf(")\n");
}