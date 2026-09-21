#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extract_elements(const int *list, size_t list_length, size_t start_index,
                     size_t element_count, int **result)
{
    int *extracted;
    size_t bytes;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (start_index > list_length ||
        element_count > list_length - start_index) {
        return -1;
    }

    if (element_count == 0) {
        return 0;
    }

    if (list == NULL || element_count > SIZE_MAX / sizeof(*extracted)) {
        return -1;
    }

    bytes = element_count * sizeof(*extracted);
    extracted = malloc(bytes);
    if (extracted == NULL) {
        return -1;
    }

    memcpy(extracted, &list[start_index], bytes);
    *result = extracted;

    return 0;
}

int main(void)
{
    const int list[] = {10, 20, 30, 40, 50, 60};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    const size_t start_index = 2;
    const size_t element_count = 3;
    int *extracted = NULL;
    size_t i;

    if (extract_elements(list, list_length, start_index, element_count,
                         &extracted) != 0) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < element_count; ++i) {
        if (printf("%d%c", extracted[i],
                   i + 1 == element_count ? '\n' : ' ') < 0) {
            free(extracted);
            return EXIT_FAILURE;
        }
    }

    free(extracted);
    return EXIT_SUCCESS;
}