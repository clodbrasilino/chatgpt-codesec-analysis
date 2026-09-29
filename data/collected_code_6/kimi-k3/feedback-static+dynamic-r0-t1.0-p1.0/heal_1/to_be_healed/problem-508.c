#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 */
bool areCommonElementsInSameOrder(int* list1, int size1, int* list2, int size2) {
    int i = 0, j = 0;
    while (i < size1 && j < size2) {
        if (list1[i] == list2[j]) {
            i++;
        }
        j++;
    }
    return i == size1;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 3, 5};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    if (areCommonElementsInSameOrder(list1, size1, list2, size2)) {
        printf("Common elements are in the same order.\n");
    } else {
        printf("Common elements are not in the same order.\n");
    }

    return 0;
}