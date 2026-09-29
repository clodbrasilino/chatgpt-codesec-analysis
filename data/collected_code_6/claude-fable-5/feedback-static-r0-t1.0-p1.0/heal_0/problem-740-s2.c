#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    Pair *pairs;
    size_t count;
} Dict;

static Dict *tuple_to_dict(const int *tuple, size_t length)
{
    Dict *dict;
    size_t i;

    if (tuple == NULL || length < 2U) {
        return NULL;
    }

    dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->count = length / 2U;
    dict->pairs = malloc(dict->count * sizeof(Pair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    for (i = 0U; i < dict->count; i++) {
        dict->pairs[i].key = tuple[2U * i];
        dict->pairs[i].value = tuple[(2U * i) + 1U];
    }

    return dict;
}

static void free_dict(Dict *dict)
{
    if (dict != NULL) {
        free(dict->pairs);
        free(dict);
    }
}

static void print_dict(const Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }

    printf("{");
    for (i = 0U; i < dict->count; i++) {
        printf("%d: %d", dict->pairs[i].key, dict->pairs[i].value);
        if (i + 1U < dict->count) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    int tuple[] = {1, 5, 7, 10, 13, 5};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    Dict *dict;

    dict = tuple_to_dict(tuple, length);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    print_dict(dict);
    free_dict(dict);

    return EXIT_SUCCESS;
}