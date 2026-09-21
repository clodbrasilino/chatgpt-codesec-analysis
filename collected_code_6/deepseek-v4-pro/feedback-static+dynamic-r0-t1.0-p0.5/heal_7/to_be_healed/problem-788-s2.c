#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_len) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    size_t str_len = strnlen(str, SIZE_MAX);
    if (str_len == SIZE_MAX) {
        free(tuple);
        return NULL;
    }

    if (str_len >= SIZE_MAX - 1) {
        free(tuple);
        return NULL;
    }

    tuple->str = (char *)malloc(str_len + 1);
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    if (str_len > 0) {
        if (str_len <= strnlen(str, str_len)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple->str, str, str_len);
        } else {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
    }
    tuple->str[str_len] = '\0';

    if (list_len > 0 && list != NULL) {
        if (list_len > SIZE_MAX / sizeof(int)) {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
        tuple->list = (int *)malloc(list_len * sizeof(int));
        if (tuple->list == NULL) {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         *  'list_size' is assigned value 'list_len*sizeof(int)' here.
         */
        size_t list_size = list_len * sizeof(int);
        /* Possible weaknesses found:
         *  The comparison 'list_size <= list_len*sizeof(int)' is always true because 'list_size' and 'list_len*sizeof(int)' represent the same value. [knownConditionTrueFalse]
         *  The comparison 'list_size <= list_len*sizeof(int)' is always true because 'list_size' and 'list_len*sizeof(int)' represent the same value.
         */
        if (list_size <= list_len * sizeof(int)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple->list, list, list_size);
            tuple->list_len = list_len;
        } else {
            free(tuple->list);
            free(tuple->str);
            free(tuple);
            return NULL;
        }
    } else {
        tuple->list = NULL;
        tuple->list_len = 0;
    }

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