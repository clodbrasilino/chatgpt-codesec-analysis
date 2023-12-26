#include <stdio.h>

void findNestedListElements(const int list1[], const int size1, const int list2[], const int size2) {
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
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {2, 4, 6};
    const int size1 = sizeof(list1) / sizeof(list1[0]);
    const int size2 = sizeof(list2) / sizeof(list2[0]);

    findNestedListElements(list1, size1, list2, size2);

    return 0;
}