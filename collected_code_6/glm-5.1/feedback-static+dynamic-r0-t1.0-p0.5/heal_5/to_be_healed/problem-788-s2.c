#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    t->string = malloc(len + 1);
    if (t->string == NULL) {
        free(t);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->string, str, len);
    t->string[len] = '\0';

    if (list_size > 0) {
        if (list_size > SIZE_MAX / sizeof(int)) {
            free(t->string);
            free(t);
            return NULL;
        }
        size_t total_list_bytes = list_size * sizeof(int);
        t->list = malloc(total_list_bytes);
        if (t->list == NULL) {
            free(t->string);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->list, list, total_list_bytes);
    } else {
        t->list = NULL;
    }

    t->list_size = list_size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->string);
        free(t->list);
        free(t);
    }
}

int main(void) {
    const char *str = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *t = create_tuple(str, list, list_size);
    if (t == NULL) {
        return EXIT_FAILURE;
    }

    printf("String: %s\n", t->string);
    printf("List: ");
    for (size_t i = 0; i < t->list_size; i++) {
        printf("%d ", t->list[i]);
    }
    printf("\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}