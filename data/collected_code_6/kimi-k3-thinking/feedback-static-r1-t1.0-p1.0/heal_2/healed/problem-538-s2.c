#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char **items;
    size_t size;
} StringTuple;

StringTuple *string_list_to_tuple(const char *list[], size_t count)
{
    if (list == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    StringTuple *tuple = malloc(sizeof(StringTuple));
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
        if (list[i] == NULL) {
            goto fail;
        }

        size_t len = strnlen(list[i], MAX_STRING_LENGTH + 1);
        if (len > MAX_STRING_LENGTH) {
            goto fail;
        }

        size_t dest_capacity = len + 1;

        tuple->items[i] = malloc(dest_capacity);
        if (tuple->items[i] == NULL) {
            goto fail;
        }

        if (len + 1 > dest_capacity) {
            free(tuple->items[i]);
            tuple->items[i] = NULL;
            goto fail;
        }

        memcpy(tuple->items[i], list[i], len);
        tuple->items[i][len] = '\0';
        tuple->size++;
    }

    return tuple;

fail:
    for (size_t j = 0; j < tuple->size; j++) {
        free(tuple->items[j]);
    }
    free(tuple->items);
    free(tuple);
    return NULL;
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