#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool extract_elements(const int *list,
                             size_t list_length,
                             size_t start_index,
                             size_t element_count,
                             int **result)
{
    int *extracted;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    if (start_index > list_length ||
        element_count > list_length - start_index) {
        return false;
    }

    if (element_count == 0) {
        return true;
    }

    if (list == NULL || element_count > SIZE_MAX / sizeof(*extracted)) {
        return false;
    }

    extracted = malloc(element_count * sizeof(*extracted));
    if (extracted == NULL) {
        return false;
    }

    for (size_t i = 0; i < element_count; ++i) {
        extracted[i] = list[start_index + i];
    }

    *result = extracted;
    return true;
}

int main(void)
{
    const int list[] = {10, 20, 30, 40, 50, 60, 70};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    const size_t start_index = 2;
    const size_t element_count = 4;
    int *extracted = NULL;

    if (!extract_elements(list, list_length, start_index,
                          element_count, &extracted)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (i != 0 && putchar(' ') == EOF) {
            free(extracted);
            return EXIT_FAILURE;
        }

        if (printf("%d", extracted[i]) < 0) {
            free(extracted);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(extracted);
        return EXIT_FAILURE;
    }

    free(extracted);
    return EXIT_SUCCESS;
}