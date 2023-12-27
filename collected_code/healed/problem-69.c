#include <stdio.h>
#include <stdbool.h>

bool checkSublist(const int *list, const int *sublist, int size, int sublistSize) {
    for (int i = 0; i <= size - sublistSize; i++) {
        int j;
        for (j = 0; j < sublistSize; j++) {
            if (list[i + j] != sublist[j]) {
                break;
            }
        }
        if (j == sublistSize) {
            return true;
        }
    }
    return false;
}

int main() {
    const int list[] = {1, 2, 3, 4, 5};
    const int sublist1[] = {2, 3, 4};
    const int sublist2[] = {4, 5, 6};

    if (checkSublist(list, sublist1, sizeof(list)/sizeof(list[0]), sizeof(sublist1)/sizeof(sublist1[0]))) {
        printf("List contains sublist1\n");
    } else {
        printf("List does not contain sublist1\n");
    }

    if (checkSublist(list, sublist2, sizeof(list)/sizeof(list[0]), sizeof(sublist2)/sizeof(sublist2[0]))) {
        printf("List contains sublist2\n");
    } else {
        printf("List does not contain sublist2\n");
    }

    return 0;
}