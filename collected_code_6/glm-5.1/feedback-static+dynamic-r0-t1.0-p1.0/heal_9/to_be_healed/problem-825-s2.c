#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 9], got <no output>
  *  test case 2 failed: expected [1, 0], got <no output>
  *  test case 1 failed: expected [2, 3], got <no output>
  */

int *access_elements(const int *list, size_t list_size, const size_t *indices, size_t indices_size, size_t *out_size) {
    if (list == NULL || indices == NULL || out_size == NULL) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }

    if (indices_size == 0 || list_size == 0) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < indices_size; i++) {
        if (indices[i] >= list_size) {
            *out_size = 0;
            return NULL;
        }
    }

    int *result = malloc(indices_size * sizeof(int));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < indices_size; i++) {
        result[i] = list[indices[i]];
    }

    *out_size = indices_size;
    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 9};
    size_t list_size1 = sizeof(list1) / sizeof(list1[0]);
    size_t indices1[] = {1, 3, 4};
    size_t indices_size1 = sizeof(indices1) / sizeof(indices1[0]);
    size_t out_size1 = 0;
    int *elements1 = access_elements(list1, list_size1, indices1, indices_size1, &out_size1);
    printf("[");
    for (size_t i = 0; i < out_size1; i++) {
        printf("%d%s", elements1 ? elements1[i] : 0, i < out_size1 - 1 ? ", " : "");
    }
    printf("]\n");
    free(elements1);

    int list2[] = {2, 1};
    size_t list_size2 = sizeof(list2) / sizeof(list2[0]);
    size_t indices2[] = {1, 0};
    size_t indices_size2 = sizeof(indices2) / sizeof(indices2[0]);
    size_t out_size2 = 0;
    int *elements2 = access_elements(list2, list_size2, indices2, indices_size2, &out_size2);
    printf("[");
    for (size_t i = 0; i < out_size2; i++) {
        printf("%d%s", elements2 ? elements2[i] : 0, i < out_size2 - 1 ? ", " : "");
    }
    printf("]\n");
    free(elements2);

    int list3[] = {1, 2, 3};
    size_t list_size3 = sizeof(list3) / sizeof(list3[0]);
    size_t indices3[] = {1, 2};
    size_t indices_size3 = sizeof(indices3) / sizeof(indices3[0]);
    size_t out_size3 = 0;
    int *elements3 = access_elements(list3, list_size3, indices3, indices_size3, &out_size3);
    printf("[");
    for (size_t i = 0; i < out_size3; i++) {
        printf("%d%s", elements3 ? elements3[i] : 0, i < out_size3 - 1 ? ", " : "");
    }
    printf("]\n");
    free(elements3);

    return 0;
}