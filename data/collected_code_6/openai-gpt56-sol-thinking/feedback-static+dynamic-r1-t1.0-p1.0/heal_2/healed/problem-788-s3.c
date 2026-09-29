#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    free(tuple->list);
    free(tuple->string);
    free(tuple);
}

static Tuple *create_tuple(const char *string, size_t string_length,
                           const int *list, size_t list_length)
{
    Tuple *tuple;
    size_t i;

    if (string == NULL || (list == NULL && list_length != 0)) {
        return NULL;
    }

    if (string_length == SIZE_MAX ||
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

    for (i = 0; i < string_length; ++i) {
        tuple->string[i] = string[i];
    }
    tuple->string[string_length] = '\0';

    if (list_length != 0) {
        tuple->list = malloc(list_length * sizeof(*tuple->list));
        if (tuple->list == NULL) {
            destroy_tuple(tuple);
            return NULL;
        }

        for (i = 0; i < list_length; ++i) {
            tuple->list[i] = list[i];
        }
    }

    tuple->list_length = list_length;
    return tuple;
}

static bool print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL || tuple->string == NULL ||
        (tuple->list == NULL && tuple->list_length != 0)) {
        return false;
    }

    if (printf("(\"%s\", [", tuple->string) < 0) {
        return false;
    }

    for (i = 0; i < tuple->list_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", tuple->list[i]) < 0) {
            return false;
        }
    }

    return printf("])\n") >= 0;
}

int main(void)
{
    static const char string[] = "example";
    static const int list[] = {1, 2, 3, 4, 5};
    Tuple *tuple;
    int status = EXIT_SUCCESS;

    tuple = create_tuple(
        string,
        sizeof(string) - 1,
        list,
        sizeof(list) / sizeof(list[0])
    );

    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_tuple(tuple)) {
        status = EXIT_FAILURE;
    }

    destroy_tuple(tuple);
    return status;
}