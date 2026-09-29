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
    Dict *dict = NULL;
    size_t i;
    size_t pair_count;

    if (tuple == NULL || length < 2U) {
        return NULL;
    }

    pair_count = length / 2U;

    dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->pairs = malloc(pair_count * sizeof(Pair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    dict->count = pair_count;

    for (i = 0U; i < pair_count; i++) {
        dict->pairs[i].key = tuple[2U * i];
        dict->pairs[i].value = tuple[(2U * i) + 1U];
    }

    return dict;
}

static void dict_free(Dict *dict)
{
    if (dict != NULL) {
        free(dict->pairs);
        free(dict);
    }
}

static void dict_print(const Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        (void)printf("{}\n");
        return;
    }

    (void)printf("{");
    for (i = 0U; i < dict->count; i++) {
        (void)printf("%d: %d", dict->pairs[i].key, dict->pairs[i].value);
        if (i < (dict->count - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf("}\n");
}

int main(void)
{
    int tuple[] = {1, 5, 7, 10, 13, 5};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    Dict *dict;

    dict = tuple_to_dict(tuple, length);
    if (dict == NULL) {
        (void)fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    dict_print(dict);
    dict_free(dict);

    return EXIT_SUCCESS;
}