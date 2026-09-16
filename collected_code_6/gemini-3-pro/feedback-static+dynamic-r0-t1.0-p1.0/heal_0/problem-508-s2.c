#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkCommonElementsOrder(int* list1, int size1, int* list2, int size2) {
    if (list1 == NULL || list2 == NULL || size1 <= 0 || size2 <= 0) {
        return false;
    }

    int* common1 = (int*)malloc(size1 * sizeof(int));
    if (common1 == NULL) {
        return false;
    }

    int* common2 = (int*)malloc(size2 * sizeof(int));
    if (common2 == NULL) {
        free(common1);
        return false;
    }

    int count1 = 0;
    for (int i = 0; i < size1; i++) {
        bool found = false;
        for (int j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                found = true;
                break;
            }
        }
        if (found) {
            common1[count1++] = list1[i];
        }
    }

    int count2 = 0;
    for (int i = 0; i < size2; i++) {
        bool found = false;
        for (int j = 0; j < size1; j++) {
            if (list2[i] == list1[j]) {
                found = true;
                break;
            }
        }
        if (found) {
            common2[count2++] = list2[i];
        }
    }

    bool result = true;
    if (count1 != count2) {
        result = false;
    } else {
        for (int i = 0; i < count1; i++) {
            if (common1[i] != common2[i]) {
                result = false;
                break;
            }
        }
    }

    free(common1);
    free(common2);

    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5, 6};
    int size1 = sizeof(list1) / sizeof(list1[0]);

    int list2[] = {2, 7, 4, 8, 6};
    int size2 = sizeof(list2) / sizeof(list2[0]);

    if (checkCommonElementsOrder(list1, size1, list2, size2)) {
        printf("Common elements are in the same order.\n");
    } else {
        printf("Common elements are NOT in the same order.\n");
    }

    return 0;
}