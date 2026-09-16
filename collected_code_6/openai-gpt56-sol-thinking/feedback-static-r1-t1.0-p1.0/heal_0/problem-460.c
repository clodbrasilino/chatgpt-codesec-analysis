#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int get_first_elements(const int *const *sublists,
                       const size_t *lengths,
                       size_t sublist_count,
                       int **result)
{
    int *elements;
    size_t i;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (sublist_count == 0U) {
        return 0;
    }

    if (sublists == NULL || lengths == NULL) {
        return EINVAL;
    }

    for (i = 0U; i < sublist_count; ++i) {
        if (sublists[i] == NULL || lengths[i] == 0U) {
            return EINVAL;
        }
    }

    if (sublist_count > SIZE_MAX / sizeof(*elements)) {
        return EOVERFLOW;
    }

    elements = malloc(sublist_count * sizeof(*elements));
    if (elements == NULL) {
        return ENOMEM;
    }

    for (i = 0U; i < sublist_count; ++i) {
        elements[i] = sublists[i][0];
    }

    *result = elements;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const int *sublists[] = {first, second, third};
    const size_t lengths[] = {
        sizeof(first) / sizeof(first[0]),
        sizeof(second) / sizeof(second[0]),
        sizeof(third) / sizeof(third[0])
    };
    const size_t sublist_count = sizeof(sublists) / sizeof(sublists[0]);
    int *elements = NULL;
    size_t i;
    int status;

    status = get_first_elements(sublists, lengths, sublist_count, &elements);
    if (status != 0) {
        errno = status;
        perror("get_first_elements");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < sublist_count; ++i) {
        if (printf("%d%c", elements[i],
                   i + 1U == sublist_count ? '\n' : ' ') < 0) {
            free(elements);
            return EXIT_FAILURE;
        }
    }

    free(elements);
    return EXIT_SUCCESS;
}