#include <stdio.h>

int isConsecutive(const int list[], int size) {
    for (int i = 1; i < size; i++) {
        if (list[i] != list[i-1] + 1) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 3, 5, 7, 9};

    if (isConsecutive(list1, sizeof(list1)/sizeof(list1[0]))) {
        printf("list1 is consecutive.\n");
    }
    else {
        printf("list1 is not consecutive.\n");
    }
    
    if (isConsecutive(list2, sizeof(list2)/sizeof(list2[0]))) {
        printf("list2 is consecutive.\n");
    }
    else {
        printf("list2 is not consecutive.\n");
    }

    return 0;
}