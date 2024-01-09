#include <stdio.h>

#define MAX_SIZE 100

// Function to calculate the sum of elements in a list
int sum(int list[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += list[i];
    }
    return total;
}

// Function to find the list in a list of lists whose sum of elements is the highest
int* findHighestSumList(int listOfLists[][MAX_SIZE], int numLists, int listSizes[]) {
    int maxSum = 0;
    int* highestSumList = NULL;

    for (int i = 0; i < numLists; i++) {
        int currentSum = sum(listOfLists[i], listSizes[i]);
        if (currentSum > maxSum) {
            maxSum = currentSum;
            highestSumList = listOfLists[i];
        }
    }
    return highestSumList;
}

// Example usage
int main() {
    int listOfLists[][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10}};
    int listSizes[] = {3, 4, 3};

    int* highestSumList = findHighestSumList(listOfLists, 3, listSizes);

    printf("List with highest sum of elements: ");
    for (int i = 0; i < listSizes[highestSumList]; i++) {
        printf("%d ", highestSumList[i]);
    }

    return 0;
}