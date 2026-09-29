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
    if (tuple == NULL) {
        return;
    }

    free(tuple->string);
    free(tuple->list);
    free(tuple);
}

static Tuple *create_tuple(const char *string, size_t string_size,
                           const int *list, size_t list_length)
{
    Tuple *tuple;
    const char *terminator;
    size_t string_bytes;
    size_t list_bytes;

    if (string == NULL || string_size == 0 ||
        (list == NULL && list_length != 0)) {
        return NULL;
    }

    terminator = memchr(string, '\0', string_size);
    if (terminator == NULL) {
        return NULL;
    }

    string_bytes = (size_t)(terminator - string) + 1;

    if (list_length > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    list_bytes = list_length * sizeof(*list);

    tuple = calloc(1, sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->string = malloc(string_bytes);
    if (tuple->string == NULL) {
        destroy_tuple(tuple);
        return NULL;
    }

    if (snprintf(tuple->string, string_bytes, "%s", string) < 0) {
        destroy_tuple(tuple);
        return NULL;
    }

    if (list_length != 0) {
        tuple->list = malloc(list_bytes);
        if (tuple->list == NULL) {
            destroy_tuple(tuple);
            return NULL;
        }

        for (size_t i = 0; i < list_length; ++i) {
            tuple->list[i] = list[i];
        }
    }

    tuple->list_length = list_length;
    return tuple;
}

int main(void)
{
    static const char string[] = "example";
    static const int list[] = {1, 2, 3, 4};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    Tuple *tuple;

    tuple = create_tuple(string, sizeof(string), list, list_length);
    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(\"%s\", [", tuple->string) < 0) {
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple->list_length; ++i) {
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