#include <stdio.h>

int countLists(int** lists, int numLists) {
    int count = 0;
    
    for (int i = 0; i < numLists; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'lists[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (lists[i] != NULL) {
            count++;
        }
    }
    
    return count * count;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int list3[] = {7, 8, 9};
    int* listOfLists[] = {list1, list2, list3, NULL};
    int numLists = sizeof(listOfLists) / sizeof(listOfLists[0]);
    
    int result = countLists(listOfLists, numLists);
    printf("Number of lists squared: %d\n", result);
    
    return 0;
}
