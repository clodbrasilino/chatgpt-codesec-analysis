#include <stdio.h>

#define MAX_LENGTH 100

int** findMaxLists(int** arr, int rows) {
    int max_length = 0;
    int num_lists = 0;
    
    for (int i = 0; i < rows; i++) {
        int length = 0;
        int* list = arr[i];
        
        while (*list != -1) {
            length++;
            list++;
        }
        
        if (length > max_length) {
            max_length = length;
            num_lists = 1;
        }
        else if (length == max_length) {
            num_lists++;
        }
    }
    
    int** max_lists = (int**)malloc(num_lists * sizeof(int*));
    
    int index = 0;
    for (int i = 0; i < rows; i++) {
        int length = 0;
        int* list = arr[i];
        
        while (*list != -1) {
            length++;
            list++;
        }
        
        if (length == max_length) {
            max_lists[index] = arr[i];
            index++;
        }
    }
    
    return max_lists;
}

int main() {
    int list1[] = {1, 2, 3, -1};
    int list2[] = {4, 5, -1};
    int list3[] = {6, 7, 8, -1};
    int list4[] = {9, -1};
    int list5[] = {-1};
    
    int* input[] = {list1, list2, list3, list4, list5};
    
    int** max_lists = findMaxLists(input, 5);
    
    printf("Lists with maximum length:\n");
    for (int i = 0; i < sizeof(max_lists) / sizeof(max_lists[0]); i++) {
        int* list = max_lists[i];
        while (*list != -1) {
            printf("%d ", *list);
            list++;
        }
        printf("\n");
    }
    
    return 0;
}