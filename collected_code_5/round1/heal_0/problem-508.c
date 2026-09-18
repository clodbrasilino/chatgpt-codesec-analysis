#include <stdbool.h>
#include <stdio.h>

bool check_order(int* list1, int size1, int* list2, int size2) {
    int pointer1=0, pointer2=0;

    while (pointer1<size1 && pointer2<size2) {
        if (list1[pointer1] == list2[pointer2]) {
            pointer1++;
        }
        pointer2++;
    }

    if (pointer1<size1) {
        return false;
    } else {
        return true;
    }
}

int main() {

    int list1[5] = {1, 2, 3, 4, 5};
    int list2[10] = {1, 3, 5, 2, 6, 7, 4, 8, 9, 5};

    bool result = check_order(list1, 5, list2, 10);

    if(result) {
        printf("List 1's common elements are in order in List 2.\n");
    } else {
        printf("List 1's common elements are not in order in List 2.\n");
    }

    return 0;
}