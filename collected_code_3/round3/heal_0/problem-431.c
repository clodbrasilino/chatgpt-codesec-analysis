#include <stdbool.h>
#include <stdio.h>

bool commonElement(int *list1, int size1, int *list2, int size2) {
    for(int i = 0; i < size1; i++) {
        for(int j = 0; j < size2; j++) {
            if(list1[i] == list2[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    if(commonElement(list1, size1, list2, size2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}