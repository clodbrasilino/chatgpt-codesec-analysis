#include <stdio.h>

#define MAX_SIZE 100

int sum(const int list[], const int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += list[i];
    }
    return total;
}

const int* findHighestSumList(const int listOfLists[][MAX_SIZE], const int numLists, const int listSizes[]) {
    int maxSum = 0;
    const int* highestSumList = NULL;

    for (int i = 0; i < numLists; i++) {
        int currentSum = sum(listOfLists[i], listSizes[i]);
        if (currentSum > maxSum) {
            maxSum = currentSum;
            highestSumList = listOfLists[i];
        }
    }
    return highestSumList;
}

int main() {
    const int listOfLists[][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10}};
    const int listSizes[] = {3, 4, 3};

    const int* highestSumList = findHighestSumList(listOfLists, 3, listSizes);

    printf("List with highest sum of elements: ");
    /* Possible weaknesses found:
     *  invalid operands to binary - (have 'const int *' and 'const int (*)[100]')
     */
    for (int i = 0; i < listSizes[highestSumList - listOfLists]; i++) {
        printf("%d ", highestSumList[i]);
    }

    return 0;
}