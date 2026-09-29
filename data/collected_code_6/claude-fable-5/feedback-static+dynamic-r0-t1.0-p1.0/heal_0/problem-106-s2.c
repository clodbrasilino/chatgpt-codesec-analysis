#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *add_list_to_tuple(const int *tuple, size_t tuple_len,
                       const int *list, size_t list_len,
                       size_t *result_len)
{
    if (result_len == NULL) {
        return NULL;
    }
    if ((tuple == NULL && tuple_len > 0) || (list == NULL && list_len > 0)) {
        return NULL;
    }
    if (tuple_len > SIZE_MAX - list_len) {
        return NULL;
    }

    size_t total = tuple_len + list_len;
    if (total == 0) {
        *result_len = 0;
        return NULL;
    }

    int *result = malloc(total * sizeof(*result));
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

    int *result = add_list_to_tuple(tuple, sizeof(tuple) / sizeof(tuple[0]),
                                    list, sizeof(list) / sizeof(list[0]),
                                    &result_len);
    if (result == NULL) {
        fprintf(stderr, "Failed to combine list and tuple\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0; i < result_len; i++) {
        printf("%d", result[i]);
        if (i + 1 < result_len) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    return EXIT_SUCCESS;
}