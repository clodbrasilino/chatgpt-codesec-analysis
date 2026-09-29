#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_length;
} Tuple;

Tuple *create_tuple(const char *string, size_t string_length, const int *list, size_t list_length) {
    if (string == NULL || (list == NULL && list_length > 0)) {
        return NULL;
    }
    if (string_length > (size_t)-1 - 1) {
        return NULL;
    }
    if (list_length > (size_t)-1 / sizeof(*list)) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->string = NULL;
    tuple->list = NULL;
    tuple->list_length = 0;

    tuple->string = malloc(string_length + 1);
    if (tuple->string == NULL) {
        free(tuple);
        return NULL;
    }
    if (string_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->string, string, string_length);
    }
    tuple->string[string_length] = '\0';

    if (list_length > 0) {
        tuple->list = malloc(list_length * sizeof(*list));
        if (tuple->list == NULL) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->list, list, list_length * sizeof(*list));
    }

    tuple->list_length = list_length;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->string);
        free(tuple->list);
        free(tuple);
    }
}

int main(void) {
    const char *string = "hello";
    int list_data[] = {1, 2, 3, 4};
    size_t list_length = sizeof(list_data) / sizeof(list_data[0]);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t string_length = strlen(string);

    Tuple *tuple = create_tuple(string, string_length, list_data, list_length);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->string);
    printf("List: ");
    for (size_t i = 0; i < tuple->list_length; ++i) {
        printf("%d", tuple->list[i]);
        if (i + 1 < tuple->list_length) {
            printf(", ");
        }
    }
    printf("\n");

    free_tuple(tuple);
    return EXIT_SUCCESS;
}