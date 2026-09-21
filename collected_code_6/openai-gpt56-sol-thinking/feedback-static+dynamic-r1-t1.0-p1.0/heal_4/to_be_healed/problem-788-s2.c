#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->string, string, string_length);
    tuple->string[string_length] = '\0';

    if (list_length != 0) {
        tuple->list = malloc(list_length * sizeof(*tuple->list));
        if (tuple->list == NULL) {
            destroy_tuple(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->list, list, list_length * sizeof(*tuple->list));
    }

    tuple->list_length = list_length;
    return tuple;
}

static int print_tuple(const Tuple *tuple)
{
    size_t index;

    if (tuple == NULL || tuple->string == NULL ||
        (tuple->list == NULL && tuple->list_length != 0)) {
        return -1;
    }

    if (printf("(\"%s\", [", tuple->string) < 0) {
        return -1;
    }

    for (index = 0; index < tuple->list_length; ++index) {
        if (printf("%s%d", index == 0 ? "" : ", ",
                   tuple->list[index]) < 0) {
            return -1;
        }
    }

    return printf("])\n") < 0 ? -1 : 0;
}

int main(void)
{
    static const char string[] = "example";
    static const int list[] = {1, 2, 3, 4, 5};
    Tuple *tuple;
    int result;

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

    result = print_tuple(tuple);
    destroy_tuple(tuple);

    if (result != 0) {
        fputs("Failed to print tuple\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}