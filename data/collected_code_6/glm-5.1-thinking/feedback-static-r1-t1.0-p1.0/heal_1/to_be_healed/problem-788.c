#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_len) {
    if (str == NULL) {
        return NULL;
    }

    if (list == NULL && list_len > 0) {
        return NULL;
    }

    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
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

    if (list_len > 0) {
        t->list = (int *)malloc(list_len * sizeof(int));
        if (t->list == NULL) {
            free(t->str);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->list, list, list_len * sizeof(int));
    } else {
        t->list = NULL;
    }

    t->list_len = list_len;

    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main(void) {
    const char *str = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple(str, list, len);

    if (t != NULL) {
        free_tuple(t);
    }

    return 0;
}