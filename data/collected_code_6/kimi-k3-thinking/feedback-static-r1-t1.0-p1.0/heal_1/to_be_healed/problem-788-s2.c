#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size)
{
    Tuple *t;

    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    t->str = (char *)malloc(strlen(str) + 1);
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
        t->list = (int *)malloc(list_size * sizeof(int));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->list, list, list_size * sizeof(int));
    }

    return t;
}

void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main(void)
{
    const char *str = "hello";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t i;
    Tuple *t;

    t = create_tuple(str, list, list_size);
    if (t == NULL) {
        fprintf(stderr, "Error: failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple: (\"%s\", [", t->str);
    for (i = 0; i < t->list_size; i++) {
        printf("%d", t->list[i]);
        if (i + 1 < t->list_size) {
            printf(", ");
        }
    }
    printf("])\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}