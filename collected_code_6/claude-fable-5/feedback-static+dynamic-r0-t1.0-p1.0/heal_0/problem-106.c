#include <stdio.h>
#include <stdlib.h>

int *add_list_to_tuple(const int *tuple, size_t tuple_len,
                       const int *list, size_t list_len,
                       size_t *result_len)
{
    if (result_len == NULL) {
        return NULL;
    }

    *result_len = 0;

    if ((tuple == NULL && tuple_len > 0) ||
        (list == NULL && list_len > 0)) {
        return NULL;
    }

    if (tuple_len > SIZE_MAX - list_len) {
        return NULL;
    }

    size_t total = tuple_len + list_len;

    if (total == 0) {
        return NULL;
    }

    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = malloc(total * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < tuple_len; i++) {
        result[i] = tuple[i];
    }

    for (size_t i = 0; i < list_len; i++) {
        result[tuple_len + i] = list[i];
    }

    *result_len = total;
    return result;
}

int main(void)
{
    int tuple[] = {9, 10};
    int list[] = {5, 6, 7};
    size_t result_len = 0;

    int *result = add_list_to_tuple(tuple,
                                    sizeof(tuple) / sizeof(tuple[0]),
                                    list,
                                    sizeof(list) / sizeof(list[0]),
                                    &result_len);

    if (result == NULL) {
        fprintf(stderr, "Failed to combine tuple and list\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0; i < result_len; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", result[i]);
    }
    printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}