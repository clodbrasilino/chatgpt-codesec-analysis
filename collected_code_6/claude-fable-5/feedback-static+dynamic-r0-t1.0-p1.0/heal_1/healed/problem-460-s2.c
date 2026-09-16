#include <stdio.h>
#include <stdlib.h>

int *get_first_elements(int **lists, const size_t *lengths, size_t count)
{
    int *result;
    size_t i;

    if (lists == NULL || lengths == NULL || count == 0U) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        if (lists[i] == NULL || lengths[i] == 0U) {
            free(result);
            return NULL;
        }
        result[i] = lists[i][0];
    }

    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {6, 7, 8, 9};
    int *lists[] = {list1, list2, list3};
    const size_t lengths[] = {3U, 2U, 4U};
    size_t count = sizeof(lists) / sizeof(lists[0]);
    int *firsts;
    size_t i;

    firsts = get_first_elements(lists, lengths, count);
    if (firsts == NULL) {
        fprintf(stderr, "Failed to extract first elements\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        printf("%d\n", firsts[i]);
    }

    free(firsts);
    return EXIT_SUCCESS;
}