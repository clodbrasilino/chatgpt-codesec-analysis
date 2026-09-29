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

static Tuple *create_tuple(const char *string, const int *list, size_t list_length)
{
    Tuple *tuple;
    size_t string_length;
    size_t string_size;
    size_t list_size;

    if (string == NULL || (list == NULL && list_length != 0)) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    string_length = strlen(string);

    if (string_length == SIZE_MAX) {
        return NULL;
    }

    string_size = string_length + 1;

    if (list_length > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    list_size = list_length * sizeof(*list);

    tuple = calloc(1, sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->string = malloc(string_size);
    if (tuple->string == NULL) {
        destroy_tuple(tuple);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->string, string, string_size);

    if (list_size != 0) {
        tuple->list = malloc(list_size);
        if (tuple->list == NULL) {
            destroy_tuple(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->list, list, list_size);
    }

    tuple->list_length = list_length;
    return tuple;
}

int main(void)
{
    const int list[] = {1, 2, 3, 4};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    Tuple *tuple;
    size_t i;

    tuple = create_tuple("example", list, list_length);
    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(\"%s\", [", tuple->string) < 0) {
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