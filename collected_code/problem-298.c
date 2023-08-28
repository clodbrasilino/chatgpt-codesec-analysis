#include <stdio.h>

void findNestedListElements(int list1[], int size1, int list2[], int size2) {
    printf("Nested list elements present in another list: ");
    for (int i = 0; i < size1; i++) {
        int found = 0;
        for (int j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                found = 1;
                break;
            }
        }
        if (found) {
            printf("%d ", list1[i]);
        }
    }
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 4, 6};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    findNestedListElements(list1, size1, list2, size2);

    return 0;
}