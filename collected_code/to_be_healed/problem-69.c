#include <stdio.h>
#include <stdbool.h>

bool checkSublist(int list[], int sublist[], int size, int sublistSize) {
    for (int i = 0; i <= size - sublistSize; i++) {
        int j;
        for (j = 0; j < sublistSize; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'sublist[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list[i+j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list[i+j] != sublist[j]) {
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
    int list[] = {1, 2, 3, 4, 5};
    int sublist1[] = {2, 3, 4};
    int sublist2[] = {4, 5, 6};

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