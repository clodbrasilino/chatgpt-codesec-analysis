#include <stdio.h>
#include <stdbool.h>

bool isEqual(const int list1[], const int list2[], int size1, int size2) {
    if (size1 != size2) {
        return false;
    }
    for (int i = 0; i < size1; i++) {
        if (list1[i] != list2[i]) {
            return false;
        }
    }
    return true;
}

bool isSubset(const int list1[], const int list2[], int size1, int size2) {
    if (size1 > size2) {
        return false;
    }
    for (int i = 0; i <= size2 - size1; i++) {
        if (isEqual(list1, list2 + i, size1, size2 - i)) {
            return true;
        }
    }
    return false;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {5, 4, 3, 2, 1, 0};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    
    if (isSubset(list1, list2, size1, size2)) {
        printf("list1 is a subset of list2\n");
    } else {
        printf("list1 is not a subset of list2\n");
    }
    return 0;
}