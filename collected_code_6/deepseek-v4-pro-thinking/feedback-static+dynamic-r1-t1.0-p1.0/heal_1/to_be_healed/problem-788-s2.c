#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *string, const int *list, size_t list_size) {
    Tuple *tuple;
    char *string_copy;
    int *list_copy;

    if (!string || (list_size > 0 && !list)) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->string = NULL;
    tuple->list = NULL;
    tuple->list_size = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    string_copy = malloc(strlen(string) + 1);
    if (!string_copy) {
        free(tuple);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(string_copy, string);
    tuple->string = string_copy;

    if (list_size > 0) {
        list_copy = malloc(list_size * sizeof(*list_copy));
        if (!list_copy) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list_copy, list, list_size * sizeof(*list_copy));
        tuple->list = list_copy;
        tuple->list_size = list_size;
    }

    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }

    free(tuple->string);
    free(tuple->list);
    free(tuple);
}

int main(void) {
    int numbers[] = {1, 2, 3};
    Tuple *tuple = create_tuple("example", numbers, sizeof(numbers) / sizeof(numbers[0]));

    if (!tuple) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->string);
    printf("List: ");

    for (size_t i = 0; i < tuple->list_size; ++i) {
        printf("%d%s", tuple->list[i], (i + 1 < tuple->list_size) ? " " : "");
    }

    printf("\n");

    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}