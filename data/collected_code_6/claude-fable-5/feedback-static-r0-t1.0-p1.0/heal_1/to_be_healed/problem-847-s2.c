#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t size;
} Tuple;

typedef struct {
    int *items;
    size_t size;
} List;

List *copy_list_from_tuple(const Tuple *t)
{
    List *l;

    if (t == NULL || t->items == NULL || t->size == 0) {
        return NULL;
    }

    if (t->size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    l = malloc(sizeof(List));
    if (l == NULL) {
        return NULL;
    }

    l->items = malloc(t->size * sizeof(int));
    if (l->items == NULL) {
        free(l);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(l->items, t->items, t->size * sizeof(int));
    l->size = t->size;

    return l;
}

void free_list(List *l)
{
    if (l != NULL) {
        free(l->items);
        free(l);
    }
}

int main(void)
{
    int data[] = {42};
    Tuple singleton;
    List *copied;
    size_t i;

    singleton.items = data;
    singleton.size = 1;

    copied = copy_list_from_tuple(&singleton);
    if (copied == NULL) {
        fprintf(stderr, "Failed to copy list from tuple\n");
        return EXIT_FAILURE;
    }

    printf("Copied list contents:\n");
    for (i = 0; i < copied->size; i++) {
        printf("%d\n", copied->items[i]);
    }

    free_list(copied);

    return EXIT_SUCCESS;
}