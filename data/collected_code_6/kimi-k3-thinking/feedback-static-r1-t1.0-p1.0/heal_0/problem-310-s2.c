#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

int string_to_tuple(const char *str, Tuple *tuple)
{
    size_t len;
    size_t i;

    if (str == NULL || tuple == NULL) {
        return -1;
    }

    tuple->items = NULL;
    tuple->size = 0;

    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    tuple->items = malloc(len * sizeof(*tuple->items));
    if (tuple->items == NULL) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        tuple->items[i] = malloc(2 * sizeof(**tuple->items));
        if (tuple->items[i] == NULL) {
            while (i > 0) {
                free(tuple->items[--i]);
            }
            free(tuple->items);
            tuple->items = NULL;
            return -1;
        }
        tuple->items[i][0] = str[i];
        tuple->items[i][1] = '\0';
    }

    tuple->size = len;
    return 0;
}

void free_tuple(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    printf("(");
    for (i = 0; i < tuple->size; i++) {
        printf("'%s'", tuple->items[i]);
        if (i + 1 < tuple->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *str = "hello";
    Tuple tuple;

    if (string_to_tuple(str, &tuple) != 0) {
        fprintf(stderr, "Error: failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(&tuple);

    free_tuple(&tuple);

    return EXIT_SUCCESS;
}