#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list3' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int* find_common_index(int *list1, int *list2, int *list3, int size, int *result_size) {
    int *common = (int *)malloc(size * sizeof(int));
    if (common == NULL) return NULL;
    
    *result_size = 0;

    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            common[(*result_size)++] = list1[i];
        }
    }

    if (*result_size > 0) {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'common' nulled but not freed upon failure [memleakOnRealloc]
         */
        common = (int *)realloc(common, (*result_size) * sizeof(int));
    } else {
        free(common);
        common = NULL;
    }

    return common;
}

int main() {
    int list1[] = {1, 2, 3, 4};
    int list2[] = {1, 2, 5, 4};
    int list3[] = {1, 8, 3, 4};
    int size = 4;
    int result_size;

    int *common = find_common_index(list1, list2, list3, size, &result_size);

    if (common != NULL) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", common[i]);
        }
        free(common);
    } else {
        printf("No common elements found.\n");
    }

    return 0;
}