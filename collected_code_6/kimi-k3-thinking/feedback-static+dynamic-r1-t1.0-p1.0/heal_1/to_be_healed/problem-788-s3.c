#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }
    if (list_size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(*t));
    if (t == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    t->str = malloc(strlen(str) + 1);
    if (t->str == NULL) {
        free(t);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(t->str, str);

    t->list = NULL;
    t->list_size = list_size;

    if (list_size > 0) {
        t->list = malloc(list_size * sizeof(*t->list));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->list, list, list_size * sizeof(*t->list));
    }

    return t;
}

void destroy_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple("hello", list, list_size);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", t->str);
    printf("List:");
    for (size_t i = 0; i < t->list_size; i++) {
        printf(" %d", t->list[i]);
    }
    printf("\n");

    destroy_tuple(t);
    t = NULL;

    return EXIT_SUCCESS;
}