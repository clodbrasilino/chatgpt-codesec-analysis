#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list3' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 */
void find_common_elements(int *list1, int size1, int *list2, int size2, int *list3, int size3) {
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        return;
    }

    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2 && k < size3) {
        if (list1[i] == list2[j] && list2[j] == list3[k]) {
            printf("%d ", list1[i]);
            i++;
            j++;
            k++;
        } else if (list1[i] < list2[j]) {
            i++;
        } else if (list2[j] < list3[k]) {
            j++;
        } else {
            k++;
        }
    }
    printf("\n");
}

int main(void) {
    int list1[] = {1, 5, 10, 20, 40, 80};
    int list2[] = {6, 7, 20, 80, 100};
    int list3[] = {3, 4, 15, 20, 30, 70, 80, 120};

    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int size3 = sizeof(list3) / sizeof(list3[0]);

    find_common_elements(list1, size1, list2, size2, list3, size3);

    return 0;
}