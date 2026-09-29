#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple t;

    if (str == NULL) {
        t.str = NULL;
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(str);
        t.str = malloc(str_len + 1);
        if (t.str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        if (str_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(t.str, str, str_len);
        }
        t.str[str_len] = '\0';
    }

    if (list_len > 0 && list != NULL) {
        size_t alloc_size = list_len * sizeof(int);
        if (alloc_size / sizeof(int) != list_len) {
            free(t.str);
            fprintf(stderr, "Integer overflow detected\n");
            exit(EXIT_FAILURE);
        }
        t.list = malloc(alloc_size);
        if (t.list == NULL) {
            free(t.str);
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t.list, list, alloc_size);
    } else {
        t.list = NULL;
    }

    t.list_len = (list != NULL) ? list_len : 0;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        t->str = NULL;
        t->list = NULL;
        t->list_len = 0;
    }
}

int main(void) {
    const char *str = "hello";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    Tuple t;

    t = create_tuple(str, list, list_len);

    if (t.str != NULL) {
        printf("String: %s\n", t.str);
    }
    printf("List: ");
    for (size_t i = 0; i < t.list_len; i++) {
        printf("%d ", t.list[i]);
    }
    printf("\n");

    free_tuple(&t);

    return 0;
}