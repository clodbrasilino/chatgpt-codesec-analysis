#include <stdio.h>

#define MAX_SIZE 100

int sum(const int list[], const int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += list[i];
    }
    return total;
}

int findHighestSumListIndex(const int listOfLists[][MAX_SIZE], const int numLists, const int listSizes[]) {
    int maxSum = 0;
    int indexOfMax = 0;

    for (int i = 0; i < numLists; i++) {
        int currentSum = sum(listOfLists[i], listSizes[i]);
        if (currentSum > maxSum) {
            maxSum = currentSum;
            indexOfMax = i;
        }
    }
    return indexOfMax;
}

int main() {
    const int listOfLists[][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10}};
    const int listSizes[] = {3, 4, 3};

    const int highestSumListIndex = findHighestSumListIndex(listOfLists, 3, listSizes);

    printf("List with highest sum of elements: ");
    for (int i = 0; i < listSizes[highestSumListIndex]; i++) {
        printf("%d ", listOfLists[highestSumListIndex][i]);
    }

    return 0;
}