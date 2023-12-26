#include <stdio.h>

#define MAX_SIZE 100

// Function to calculate the sum of elements in a list
int sum(int list[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        total += list[i];
    }
    return total;
}

// Function to find the list in a list of lists whose sum of elements is the highest
int* findHighestSumList(int listOfLists[][MAX_SIZE], int numLists, int listSizes[]) {
    int maxSum = 0;
    int* highestSumList = NULL;

    for (int i = 0; i < numLists; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'listSizes[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'listOfLists[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int currentSum = sum(listOfLists[i], listSizes[i]);
        if (currentSum > maxSum) {
            maxSum = currentSum;
            /* Possible weaknesses found:
             *  Cannot determine that 'listOfLists[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            highestSumList = listOfLists[i];
        }
    }
    /* Possible weaknesses found:
     *  Cannot determine that 'highestSumList' is initialized [premium-bughuntingUninit]
     */
    return highestSumList;
}

// Example usage
int main() {
    int listOfLists[][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10}};
    int listSizes[] = {3, 4, 3};

    int* highestSumList = findHighestSumList(listOfLists, 3, listSizes);

    printf("List with highest sum of elements: ");
    /* Possible weaknesses found:
     *  array subscript is not an integer
     */
    for (int i = 0; i < listSizes[highestSumList]; i++) {
        printf("%d ", highestSumList[i]);
    }

    return 0;
}