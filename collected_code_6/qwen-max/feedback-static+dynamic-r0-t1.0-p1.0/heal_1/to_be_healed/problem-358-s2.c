#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int* modulo_division(int* list1, int len1, int* list2, int len2, int *result_len) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_len==NULL' is not redundant
     */
    if (len1 == 0 || len2 == 0 || list1 == NULL || list2 == NULL || result_len == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'result_len==NULL' is redundant or there is possible null pointer dereference: result_len. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *result_len = -1;
        return NULL;
    }

    int min_len = (len1 < len2) ? len1 : len2;
    int* result = (int*)malloc(min_len * sizeof(int));
    if (result == NULL) {
        *result_len = -1;
        return NULL;
    }

    for (int i = 0; i < min_len; ++i) {
        if (list2[i] == 0) {
            free(result);
            *result_len = -1;
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }

    *result_len = min_len;
    return result;
}

int main() {
    int list1[] = {10, 20, 30};
    int list2[] = {3, 4, 5};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);
    int result_len;

    int* result = modulo_division(list1, len1, list2, len2, &result_len);

    if (result_len == -1) {
        printf("Error in calculation.\n");
        return 1;
    }

    for (int i = 0; i < result_len; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}