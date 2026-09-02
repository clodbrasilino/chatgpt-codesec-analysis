#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int* list_modulo(int *list1, int len1, int *list2, int len2, int *result_len) {
    if (len1 != len2 || len1 == 0) {
        *result_len = 0;
        return NULL;
    }
    
    int *result = (int *)malloc(len1 * sizeof(int));
    if (result == NULL) {
        *result_len = 0;
        return NULL;
    }

    for (int i = 0; i < len1; ++i) {
        if (list2[i] == 0) {
            free(result);
            *result_len = 0;
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }

    *result_len = len1;
    return result;
}

int main() {
    int list1[] = {10, 20, 30, 40};
    int list2[] = {3, 4, 5, 6};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);
    int result_len;

    int *result = list_modulo(list1, len1, list2, len2, &result_len);

    if (result != NULL) {
        for (int i = 0; i < result_len; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    } else {
        printf("Error in modulo operation.\n");
    }

    return 0;
}