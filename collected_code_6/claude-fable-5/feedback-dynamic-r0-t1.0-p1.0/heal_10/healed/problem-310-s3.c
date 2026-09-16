#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *items;
    size_t count;
} Tuple;

Tuple *string_to_tuple(const char *str);
void free_tuple(Tuple *tuple);
void print_tuple(const Tuple *tuple);

Tuple *string_to_tuple(const char *str)
{
    Tuple *tuple;
    size_t length;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    length = strlen(str);

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = (char *)malloc((length + 1U) * sizeof(char));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (i = 0U; i < length; i++) {
        tuple->items[i] = str[i];
    }
    tuple->items[length] = '\0';
    tuple->count = length;

    return tuple;
}

void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        if (tuple->items != NULL) {
            free(tuple->items);
            tuple->items = NULL;
        }
        tuple->count = 0U;
        free(tuple);
    }
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if ((tuple == NULL) || (tuple->items == NULL)) {
        return;
    }

    (void)fputs("[", stdout);
    for (i = 0U; i < tuple->count; i++) {
        (void)printf("'%c'", tuple->items[i]);
        if ((i + 1U) < tuple->count) {
            (void)fputs(", ", stdout);
        }
    }
    (void)fputs("]\n", stdout);
    (void)fflush(stdout);
}

int main(void)
{
    const char *inputs[] = { "python3.0", "item1", "15.10" };
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    size_t i;

    for (i = 0U; i < num_inputs; i++) {
        Tuple *tuple = string_to_tuple(inputs[i]);

        if (tuple == NULL) {
            (void)fprintf(stderr, "Failed to convert string to tuple\n");
            return EXIT_FAILURE;
        }

        print_tuple(tuple);
        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}