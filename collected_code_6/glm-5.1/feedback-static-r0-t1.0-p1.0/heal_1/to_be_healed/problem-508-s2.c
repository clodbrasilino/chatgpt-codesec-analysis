#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 */
bool are_common_elements_in_same_order(int *list1, int size1, int *list2, int size2) {
    if (list1 == NULL || size1 <= 0 || list2 == NULL || size2 <= 0) {
        return true;
    }

    int *common = (int *)malloc(size1 * sizeof(int));
    if (common == NULL) {
        return false;
    }

    int count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    bool found;
    for (int i = 0; i < size1; i++) {
        found = false;
        for (int j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                found = true;
                break;
            }
        }
        if (found) {
            common[count++] = list1[i];
        }
    }

    if (count <= 1) {
        free(common);
        return true;
    }

    int idx = 0;
    for (int i = 0; i < size2; i++) {
        if (list2[i] == common[idx]) {
            idx++;
            if (idx == count) {
                break;
            }
        }
    }

    free(common);
    return idx == count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {9, 2, 8, 3, 7, 4, 6};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    bool result = are_common_elements_in_same_order(list1, size1, list2, size2);

    printf("%d\n", result);

    return 0;
}