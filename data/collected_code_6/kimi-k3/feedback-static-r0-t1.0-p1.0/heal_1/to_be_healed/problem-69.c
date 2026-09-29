#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'sublist' can be declared as pointer to const [constParameterPointer]
 */
int containsSublist(int *list, int listSize, int *sublist, int sublistSize) {
    if (sublistSize == 0) {
        return 1;
    }
    if (listSize < sublistSize) {
        return 0;
    }
    for (int i = 0; i <= listSize - sublistSize; i++) {
        int found = 1;
        for (int j = 0; j < sublistSize; j++) {
            if (list[i + j] != sublist[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sublist[] = {4, 5, 6};
    int listSize = sizeof(list) / sizeof(list[0]);
    int sublistSize = sizeof(sublist) / sizeof(sublist[0]);

    if (containsSublist(list, listSize, sublist, sublistSize)) {
        printf("The list contains the sublist.\n");
    } else {
        printf("The list does not contain the sublist.\n");
    }

    return 0;
}