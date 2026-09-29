#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int* multiply_lists(int *list1, int len1, int *list2, int len2, int *result_len) {
    if (len1 != len2) return NULL;
    
    int *result = (int *)malloc(len1 * sizeof(int));
    if (result == NULL) return NULL;
    
    for (int i = 0; i < len1; ++i) {
        result[i] = list1[i] * list2[i];
    }
    
    *result_len = len1;
    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);
    int result_len;

    int *result = multiply_lists(list1, len1, list2, len2, &result_len);
    if (result == NULL) {
        printf("Error: Lists have different lengths.\n");
        return 1;
    }

    for (int i = 0; i < result_len; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}