#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple *tuple = NULL;
    char *str_copy = NULL;
    int *list_copy = NULL;

    if (str == NULL || list == NULL || list_len == 0) {
        return NULL;
    }

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_copy = (char *)malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        free(tuple);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str_copy, str);

    list_copy = (int *)malloc(list_len * sizeof(int));
    if (list_copy == NULL) {
        free(str_copy);
        free(tuple);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list_copy, list, list_len * sizeof(int));

    tuple->str = str_copy;
    tuple->list = list_copy;
    tuple->list_len = list_len;

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple->list);
        free(tuple);
    }
}

int main(void) {
    const char *str = "hello";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    Tuple *tuple = create_tuple(str, list, list_len);

    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->str);
    printf("List: ");
    for (size_t i = 0; i < tuple->list_len; i++) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");

    free_tuple(tuple);
    return EXIT_SUCCESS;
}