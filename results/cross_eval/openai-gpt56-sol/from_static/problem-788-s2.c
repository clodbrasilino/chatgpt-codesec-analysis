#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_length;
} Tuple;

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->string);
    free(tuple->list);
    free(tuple);
}

static Tuple *tuple_create(const char *string, size_t string_length,
                           const int *list, size_t list_length)
{
    if (string == NULL || (list == NULL && list_length != 0)) {
        return NULL;
    }

    if (string_length == SIZE_MAX ||
        list_length > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    size_t string_size = string_length + 1;
    size_t list_size = list_length * sizeof(*list);

    Tuple *tuple = calloc(1, sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->string = malloc(string_size);
    if (tuple->string == NULL) {
        tuple_destroy(tuple);
        return NULL;
    }

    if (string_length > 0) {
        memmove(tuple->string, string, string_length);
    }
    tuple->string[string_length] = '\0';

    if (list_length > 0) {
        tuple->list = malloc(list_size);
        if (tuple->list == NULL) {
            tuple_destroy(tuple);
            return NULL;
        }

        memmove(tuple->list, list, list_size);
    }

    tuple->list_length = list_length;
    return tuple;
}

int main(void)
{
    static const char string[] = "example";
    static const int list[] = {1, 2, 3, 4, 5};

    const size_t string_length = sizeof(string) - 1;
    const size_t list_length = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = tuple_create(string, string_length, list, list_length);
    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(%s, [", tuple->string) < 0) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->list_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", tuple->list[i]) < 0) {
            tuple_destroy(tuple);
            return EXIT_FAILURE;
        }
    }

    if (puts("])") == EOF) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }

    tuple_destroy(tuple);
    return EXIT_SUCCESS;
}