#include <stdio.h>
#include <stdbool.h>

bool checkOrder(int list1[], int size1, int list2[], int size2) {
    int i, j, last_found_index = -1;
    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if(list1[i] == list2[j]) {
                if(j < last_found_index)
                    return false;
                last_found_index = j;
                break;
            }
        }
    }
    return true;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {5, 4, 3, 2, 1};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    if(checkOrder(list1, size1, list2, size2))
        printf("Common elements are in the same order.\n");
    else
        printf("Common elements are not in the same order.\n");

    return 0;
}