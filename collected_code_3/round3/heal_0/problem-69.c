#include <stdio.h>
#include <stdbool.h>

bool isSublist(int *list, int listSize, int *subList, int subListSize) {
    int i, j;
    for (i = 0; i <= listSize - subListSize; i++) {
        for (j = 0; j < subListSize; j++) {
            if (list[i + j] != subList[j]) {
                break;
            }
        }
        if (j == subListSize) {
            return true;
        }
    }
    return false;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int subList[] = {5, 6, 7};

    int listSize = sizeof(list) / sizeof(list[0]);
    int subListSize = sizeof(subList) / sizeof(subList[0]);

    if (isSublist(list, listSize, subList, subListSize)) {
        printf("Sublist found\n");
    } else {
        printf("Sublist not found\n");
    }

    return 0;
}