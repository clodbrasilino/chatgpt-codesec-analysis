#include <stdio.h>

void reverseList(int arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[start]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int temp = arr[start];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[end]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

void reverseListOfLists(int** lists, int numOfLists, int* sizes) {
    for (int i = 0; i < numOfLists; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'lists[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'sizes[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        reverseList(lists[i], sizes[i]);
    }
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};
    int list3[] = {11, 12, 13, 14, 15};

    int* listOfLists[] = {list1, list2, list3};
    int sizes[] = {5, 5, 5};

    reverseListOfLists(listOfLists, 3, sizes);

    for (int i = 0; i < 3; i++) {
        printf("Reversed List %d: ", i + 1);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", listOfLists[i][j]);
        }
        printf("\n");
    }

    return 0;
}