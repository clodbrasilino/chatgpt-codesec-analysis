#include <stdio.h>
#include <stdlib.h>

size_t find_common_index_elements(const int *list1, const int *list2,
                                  const int *list3, size_t len,
                                  int *result, size_t result_capacity)
{
    size_t count = 0;
    size_t i;

    if (list1 == NULL || list2 == NULL || list3 == NULL || result == NULL) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            if (count < result_capacity) {
                result[count] = list1[i];
                count++;
            } else {
                break;
            }
        }
    }

    return count;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6, 7};
    int list2[] = {0, 2, 3, 9, 5, 8, 7};
    int list3[] = {1, 2, 3, 7, 5, 6, 7};
    size_t len = sizeof(list1) / sizeof(list1[0]);
    int *result;
    size_t count;
    size_t i;

    result = malloc(len * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    count = find_common_index_elements(list1, list2, list3, len, result, len);

    if (count == 0) {
        printf("No common index elements found\n");
    } else {
        printf("Common index elements: ");
        for (i = 0; i < count; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}