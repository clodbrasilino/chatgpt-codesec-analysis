#include <stdio.h>
#include <stdlib.h>

int *add_tuple_to_list(const int *list, size_t list_len,
                       const int *tuple, size_t tuple_len,
                       size_t *out_len)
{
    if (out_len == NULL) {
        return NULL;
    }
    *out_len = 0;
    if ((list == NULL && list_len > 0) || (tuple == NULL && tuple_len > 0)) {
        return NULL;
    }
    if (list_len > SIZE_MAX / sizeof(int) - tuple_len) {
        return NULL;
    }

    size_t total = list_len + tuple_len;
    if (total == 0) {
        return NULL;
    }

    int *result = malloc(total * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < list_len; i++) {
        result[i] = list[i];
    }
    for (size_t i = 0; i < tuple_len; i++) {
        result[list_len + i] = tuple[i];
    }

    *out_len = total;
    return result;
}

int main(void)
{
    int list[] = {5, 6, 7};
    int tuple[] = {9, 10};
    size_t result_len = 0;

    int *result = add_tuple_to_list(list, sizeof(list) / sizeof(list[0]),
                                    tuple, sizeof(tuple) / sizeof(tuple[0]),
                                    &result_len);
    if (result == NULL) {
        fprintf(stderr, "Failed to combine list and tuple\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < result_len; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", result[i]);
    }
    printf("]\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}