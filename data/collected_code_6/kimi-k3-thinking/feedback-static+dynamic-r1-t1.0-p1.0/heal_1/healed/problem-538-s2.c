#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char **items;
    size_t size;
} StringTuple;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

StringTuple *string_list_to_tuple(const char *list[], size_t count)
{
    StringTuple *tuple;

    if (list == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = malloc(count * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = 0;

    for (size_t i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            for (size_t j = 0; j < tuple->size; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        len = bounded_strlen(list[i], MAX_STRING_LENGTH);

        tuple->items[i] = malloc(len + 1);
        if (tuple->items[i] == NULL) {
            for (size_t j = 0; j < tuple->size; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        memcpy(tuple->items[i], list[i], len);
        tuple->items[i][len] = '\0';
        tuple->size++;
    }

    return tuple;
}

void free_string_tuple(StringTuple *tuple)
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

void print_string_tuple(const StringTuple *tuple)
{
    if (tuple == NULL) {
        printf("()\n");
        return;
    }

    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("\"%s\"", tuple->items[i]);
        if (i + 1 < tuple->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *list[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(list) / sizeof(list[0]);
    StringTuple *tuple = string_list_to_tuple(list, count);

    if (tuple == NULL) {
        fprintf(stderr, "Error: failed to convert string list to tuple\n");
        return EXIT_FAILURE;
    }

    print_string_tuple(tuple);

    free_string_tuple(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}