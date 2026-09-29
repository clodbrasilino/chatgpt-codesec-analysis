#include <stdio.h>
    
int* findHighestSumList(int **lists, int *listLengths, int numLists) {
    if(!lists || !listLengths || numLists <= 0) {
        return NULL;
    }

    int highestSum = 0;
    int *highestSumList = NULL;

    for(int i = 0; i < numLists; i++) {
        int currentSum = 0;
        for(int j = 0; j < listLengths[i]; j++) {
            currentSum += lists[i][j];
        }
        
        if(currentSum > highestSum) {
            highestSum = currentSum;
            highestSumList = lists[i];
        }
    }
    return highestSumList;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};

    int *lists[] = {list1, list2, list3};
    int listLengths[] = {5, 5, 5};

    int *highestSumList = findHighestSumList(lists, listLengths, 3);

    if(highestSumList == NULL) {
        printf("No list \n");
    } else {
        for(int i = 0; i < 5; i++) {
            printf("%d ", highestSumList[i]);
        }
    }

    return 0;
}