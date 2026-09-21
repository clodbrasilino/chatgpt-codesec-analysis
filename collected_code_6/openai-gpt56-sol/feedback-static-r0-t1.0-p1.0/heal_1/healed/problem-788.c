#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_length;
} Tuple;

static void destroy_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->string);
        free(tuple->list);
        free(tuple);
    }
}

static Tuple *create_tuple(const char *string, size_t string_length,
                           const int *list, size_t list_length)
{
    Tuple *tuple;

    if (string == NULL ||
        (list == NULL && list_length != 0) ||
        string_length == SIZE_MAX ||
        list_length > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    tuple = calloc(1, sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->string = malloc(string_length + 1);
    if (tuple->string == NULL) {
        destroy_tuple(tuple);
        return NULL;
    }

    if (string_length != 0) {
        memcpy(tuple->string, string, string_length);
    }
    tuple->string[string_length] = '\0';

    if (list_length != 0) {
        tuple->list = malloc(list_length * sizeof(*tuple->list));
        if (tuple->list == NULL) {
            destroy_tuple(tuple);
            return NULL;
        }

        memcpy(tuple->list, list, list_length * sizeof(*tuple->list));
    }

    tuple->list_length = list_length;
    return tuple;
}

int main(void)
{
    static const char string[] = "example";
    const int list[] = {10, 20, 30, 40};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = create_tuple(string, sizeof(string) - 1, list, list_length);
    size_t i;

    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(%s, [", tuple->string) < 0) {
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple->list_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", tuple->list[i]) < 0) {
            destroy_tuple(tuple);
            return EXIT_FAILURE;
        }
    }

    if (puts("])") == EOF) {
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }

    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}