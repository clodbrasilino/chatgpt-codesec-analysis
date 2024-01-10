#include <stdio.h>

int countLists(int** lists, const int numLists) {
    int count = 0;
    
    for (int i = 0; i < numLists; i++) {
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
    const int numLists = sizeof(listOfLists) / sizeof(listOfLists[0]) - 1;
    
    int result = countLists(listOfLists, numLists);
    printf("Number of lists squared: %d\n", result);
    
    return 0;
}