#include <stdio.h>
#define SIZE 10

int* findHighestSumList(int* lists[SIZE], int size[SIZE], int num) {
    int sum=0, maxSum=0;
    int* maxList = NULL;
    for(int i=0; i<num; i++) {
        sum = 0;
        for(int j=0; j<size[i]; j++) {
            sum += lists[i][j];
        }
        if(sum > maxSum) {
            maxSum = sum;
            maxList = lists[i];
        }
    }
    return maxList;
}

int main() {
    int size[SIZE] = {3, 5, 4, 1, 6};
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7, 8};
    int arr3[] = {9, 10, 11, 12};
    int arr4[] = {13};
    int arr5[] = {14, 15, 16, 17, 18, 19};
    
    int *lists[SIZE] = {arr1, arr2, arr3, arr4, arr5};

    int *maxList = findHighestSumList(lists, size, 5);

    /* Possible weaknesses found:
     *  'int *' and 'int **' are not pointers to compatible types
     */
    for(int i = 0; i < size[ maxList - lists]; i++) {
        printf("%d ", maxList[i]);
    }
    
    return 0;
}