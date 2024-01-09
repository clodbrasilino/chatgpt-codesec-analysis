#include <stdio.h>

void findCommonElements(int list1[], int list2[], int list3[], int size1, int size2, int size3) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size3; k++) {
                if (list1[i] == list2[j] && list1[i] == list3[k]) {
                    printf("%d ", list1[i]);
                }
            }
        }
    }
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 4, 6, 8, 10};
    int list3[] = {3, 6, 9, 12, 15};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int size3 = sizeof(list3) / sizeof(list3[0]);

    findCommonElements(list1, list2, list3, size1, size2, size3);

    return 0;
}